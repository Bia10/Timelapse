#pragma once
#include <Windows.h>
#include <tchar.h>
#include "memory.h"
#include "Assembly.h"
#include "Packet.h"
#include "Mouse.h"
#include "Addresses.h"

static HWND GetMSWindowHandle() {
	HWND msHandle = nullptr;
	TCHAR buf[256] = { 0 };
	ULONG procid;
	for (HWND hwnd = GetTopWindow(nullptr); hwnd != nullptr; hwnd = GetNextWindow(hwnd, GW_HWNDNEXT)) {
		GetWindowThreadProcessId(hwnd, &procid);
		if (procid != GetCurrentProcessId()) continue;
		if (!GetClassName(hwnd, buf, 256)) continue;
		if (_tcscmp(buf, _T("MapleStoryClass")) != 0) continue;
		msHandle = hwnd;
	}
	if (!msHandle) return nullptr;

	return msHandle;
}

#pragma managed
//Get MS ProcessID
static String^ GetMSProcID() {
	int processID = GetCurrentProcessId();
	return "0x" + processID.ToString("X") + " (" + processID.ToString() + ")";
}

//Check if position is valid 
static bool isPosValid(int X, int Y) {
	return ((ReadPointerSigned(CWvsPhysicalSpace2DBase, OFS_rcMBR_left) <= X) && (ReadPointerSigned(CWvsPhysicalSpace2DBase, OFS_rcMBR_right) >= X)
		&& (ReadPointerSigned(CWvsPhysicalSpace2DBase, OFS_rcMBR_top) <= Y) && (ReadPointerSigned(CWvsPhysicalSpace2DBase, OFS_rcMBR_bottom) >= Y));
}

//Teleport to parameter position
static void Teleport(int X, int Y) {
	Log::WriteLineToConsole("Teleporting to X: " + X + " Y: " + Y);
	try {
		WritePointer(UserLocalBase, OFS_Tele, 0);
		WritePointer(UserLocalBase, OFS_TeleX, X);
		WritePointer(UserLocalBase, OFS_TeleY, Y);
		WritePointer(UserLocalBase, OFS_Tele, 1);
		//WritePointer(UserLocalBase, OFS_Tele + 4, 1);
	}
	catch (...) {
		Log::WriteLineToConsole("Error occured when trying to teleport via userLocalBase");
	}
}

//Teleport to parameter point
static void Teleport(POINT point) {
	if (isPosValid(point.x, point.y)) {
		WritePointer(UserLocalBase, OFS_TeleX, point.x);
		WritePointer(UserLocalBase, OFS_TeleY, point.y);
		WritePointer(UserLocalBase, OFS_Tele, 1);
		WritePointer(UserLocalBase, OFS_Tele + 4, 1);
	}
}
#pragma endregion

class PointerFuncs {
public:
	static const bool isHooksEnabled = true; //For the future, disable pointers that requires Codecaves or function calls

	//Retrieve Char Gender
	static String^ getCharGender() {
		const SHORT gender = Convert::ToInt16(ReadPointerShort(CharacterStatBase, OFS_Gender));
		return Convert::ToString(gender);
	}

	//Retrieve Char Skin
	static String^ getCharSkin() {
		const SHORT skin = Convert::ToInt16(ReadPointerShort(CharacterStatBase, OFS_Skin));
		return Convert::ToString(skin);
	}

	//Retrieve Char Face
	static String^ getCharFace() {
		const int face = ReadPointerSignedInt(CharacterStatBase, OFS_Face);
		return Convert::ToString(face);
	}

	//Retrieve Char Hair
	static String^ getCharHair() {
		const int hair = ReadPointerSignedInt(CharacterStatBase, OFS_Hair);
		return Convert::ToString(hair);
	}

	//Retrieve Char Level
	static String^ getCharLevel() {
		const UINT8 level = readCharValueZtlSecureFuse(*reinterpret_cast<ULONG*>(CharacterStatBase) + OFS_Level);
		if (level == 0) return "00";
		return Convert::ToString(level);
	}

	//Retrieve Char Job ID
	static SHORT getCharJobID() {
		return readShortValueZtlSecureFuse(*reinterpret_cast<ULONG*>(CharacterStatBase) + OFS_JobID);
	}

	//Retrieve Char Str
	static String^ getCharStr() {
		const SHORT charSTR = readShortValueZtlSecureFuse(*reinterpret_cast<ULONG*>(CharacterStatBase) + OFS_CharStr);
		return Convert::ToString(charSTR);
	}

	//Retrieve Char Dex
	static String^ getCharDex() {
		const SHORT charDex = readShortValueZtlSecureFuse(*reinterpret_cast<ULONG*>(CharacterStatBase) + OFS_CharDex);
		return Convert::ToString(charDex);
	}

	//Retrieve Char Int
	static String^ getCharInt() {
		const SHORT charInt = readShortValueZtlSecureFuse(*reinterpret_cast<ULONG*>(CharacterStatBase) + OFS_CharInt);
		return Convert::ToString(charInt);
	}

	//Retrieve Char Luk
	static String^ getCharLuk() {
		const SHORT charLuk = readShortValueZtlSecureFuse(*reinterpret_cast<ULONG*>(CharacterStatBase) + OFS_CharLuk);
		return Convert::ToString(charLuk);
	}

	//Retrieve Char CurHP
	static String^ getCharCurHPnew() {
		const SHORT charHP = readShortValueZtlSecureFuse(*reinterpret_cast<ULONG*>(CharacterStatBase) + OFS_CharCurHP);
		return Convert::ToString(charHP);
	}

	//Retrieve Char MaxHP
	static String^ getCharMaxHPnew() {
		const SHORT charHP = readShortValueZtlSecureFuse(*reinterpret_cast<ULONG*>(CharacterStatBase) + OFS_CharMaxHP);
		return Convert::ToString(charHP);
	}

	//Retrieve Char CurMP
	static String^ getCharCurMPnew() {
		const SHORT charMP = readShortValueZtlSecureFuse(*reinterpret_cast<ULONG*>(CharacterStatBase) + OFS_CharCurMP);
		return Convert::ToString(charMP);
	}

	//Retrieve Char MaxMP
	static String^ getCharMaxMPnew() {
		const SHORT charMP = readShortValueZtlSecureFuse(*reinterpret_cast<ULONG*>(CharacterStatBase) + OFS_CharMaxMP);
		return Convert::ToString(charMP);
	}

	//Retrieve Char AP
	static String^ getCharAp() {
		const SHORT charAP = readShortValueZtlSecureFuse(*reinterpret_cast<ULONG*>(CharacterStatBase) + OFS_CharAP);
		return Convert::ToString(charAP);
	}

	//Retrieve Char SP
	static String^ getCharSP() {
		const SHORT charSP = readShortValueZtlSecureFuse(*reinterpret_cast<ULONG*>(CharacterStatBase) + OFS_CharSP);
		return Convert::ToString(charSP);
	}

	//Retrieve Char XP
	static String^ getCharCurXP() {
		const int charCurXP = readLongValueZtlSecureFuse((ULONG*)(*(ULONG*)CharacterStatBase + OFS_CharCurXP));
		return Convert::ToString(charCurXP);
	}

	//Retrieve Char 
	static String^ getCharPop() {
		const int charPop = readShortValueZtlSecureFuse(*reinterpret_cast<ULONG*>(CharacterStatBase + OFS_CharPOP));
		return Convert::ToString(charPop);
	}

	//Retrieve Char Temp XP
	static String^ getCharTempXP() {
		const int charTempXP = readLongValueZtlSecureFuse((ULONG*)(*(ULONG*)CharacterStatBase + OFS_CharTempEXP));
		return Convert::ToString(charTempXP);
	}

	//Retrieve Char Job
	static String^ getCharJob() {
		return gcnew String(GetJobName(getCharJobID()));
	}

	//Retrieve Char HP
	static String^ getCharHP() {
		if (isHooksEnabled)
			Jump(statHookAddr, Assembly::StatHook, 0);
		else
			WriteMemory(statHookAddr, 5, 0x8D, 0x0C, 0x80, 0x3B, 0xCB);

		if (Assembly::maxHP != 0)
			Assembly::hpPercent = ((double)Assembly::curHP / Assembly::maxHP) * 100.0;

		return Assembly::hpPercent.ToString("f2") + "%";
	}

	//Retrieve Char MP
	static String^ getCharMP() {
		if (isHooksEnabled)
			Jump(statHookAddr, Assembly::StatHook, 0);
		else
			WriteMemory(statHookAddr, 5, 0x8D, 0x0C, 0x80, 0x3B, 0xCB);

		if (Assembly::maxMP != 0)
			Assembly::mpPercent = ((double)Assembly::curMP / Assembly::maxMP) * 100.0;

		return Assembly::mpPercent.ToString("f2") + "%";
	}

	//Retrieve Char EXP
	static String^ getCharEXP() {
		if (isHooksEnabled)
			Jump(statHookAddr, Assembly::StatHook, 0);
		else
			WriteMemory(statHookAddr, 5, 0x8D, 0x0C, 0x80, 0x3B, 0xCB);

		if (Assembly::maxEXP != 0)
			Assembly::expPercent = ((double)Assembly::curEXP / Assembly::maxEXP) * 100.0;

		return Assembly::expPercent.ToString("f2") + "%";
	}

	//Retrieve Char Mesos
	static UINT getCharMesos() {
		return readLongValueZtlSecureFuse((ULONG*)(*(ULONG*)CharacterStatBase + OFS_Mesos));
	}

	//Retrieve Map Name
	static String^ getMapName() {
		if (isHooksEnabled)
			Jump(mapNameHookAddr, Assembly::MapNameHook, 1);
		else
			WriteMemory(mapNameHookAddr, 6, 0x89, 0x7D, 0xD8, 0x8D, 0x4D, 0xEC);

		if (Assembly::mapNameAddr == 0x0) return "Waiting..";

		char *mapNameBuff = (char*)(Assembly::mapNameAddr + 12);
		return gcnew String(mapNameBuff);
	}

	//Retrieve Left Wall coord
	static String^ getMapLeftWall() {
		return ReadPointerSignedInt(CWvsPhysicalSpace2DBase, OFS_rcMBR_left).ToString();
	}

	//Retrieve Right Wall coord
	static String^ getMapRightWall() {
		return ReadPointerSignedInt(CWvsPhysicalSpace2DBase, OFS_rcMBR_right).ToString();
	}

	//Retrieve Top Wall coord
	static String^ getMapTopWall() {
		return ReadPointerSignedInt(CWvsPhysicalSpace2DBase, OFS_rcMBR_top).ToString();
	}

	//Retrieve Bottom Wall coord
	static String^ getMapBottomWall() {
		return ReadPointerSignedInt(CWvsPhysicalSpace2DBase, OFS_rcMBR_bottom).ToString();
	}

	//Retrieve Char Name
	static String^ getCharName() {
		String^ charName = Runtime::InteropServices::Marshal::PtrToStringAnsi((IntPtr)(void*)(ReadPointerString(CharacterStatBase, OFS_IGN)));
		if (String::IsNullOrEmpty(charName)) return "CharName";
		return charName;
	}

	//Retrieve World
	static String^ getWorld() {
		const int worldID = ReadPointer(ServerBase, OFS_World);
		if (getCharName()->Equals("CharName")) return "Null";
		switch (worldID) {
		case 0:
			return("Scania");
		case 1:
			return("Bera");
		case 2:
			return("Broa");
		case 3:
			return("Windia");
		case 4:
			return("Khaini");
		case 5:
			return("Bellocan");
		case 6:
			return("Mardia");
		case 7:
			return("Kradia");
		case 8:
			return("Yellonde");
		case 9:
			return("Demethos");
		case 10:
			return("Galicia");
		case 11:
			return("El Nido");
		case 12:
			return("Zenith");
		case 13:
			return("Arcania");
		case 14:
			return("Chaos");
		case 15:
			return("Nova");
		case 16:
			return("Regenades");
		default:
			return("Null");
		}
	}

	//Retrieve Channel
	static String^ getChannel() {
		return (ReadPointer(ServerBase, OFS_Channel) + 1).ToString();
	}

	//Retrieve MapID
	static String^ getMapID() {
		return ReadPointerSignedInt(UIMiniMapBase, m_dwFieldID).ToString();
	}

	//Retrieve Char Position
	static String^ getCharPos() {
		return "(" + ReadPointerSignedInt(UserLocalBase, OFS_CharX).ToString() + ", " + ReadPointerSignedInt(UserLocalBase, OFS_CharY).ToString() + ")";
	}

	//Retrieve Char X Position
	static String^ getCharPosX() {
		return ReadPointerSignedInt(UserLocalBase, OFS_CharX).ToString();
	}

	//Retrieve Char Y Position
	static String^ getCharPosY() {
		return ReadPointerSignedInt(UserLocalBase, OFS_CharY).ToString();
	}

	//Retrieve Mouse Position
	static String^ getMousePos() {
		return "(" + ReadMultiPointerSigned(InputBase, 2, OFS_MouseLocation, OFS_MouseX).ToString() + ", " + ReadMultiPointerSigned(InputBase, 2, OFS_MouseLocation, OFS_MouseY).ToString() + ")";
	}

	//Retrieve Mouse X Position
	static String^ getMousePosX() {
		return ReadMultiPointerSigned(InputBase, 2, OFS_MouseLocation, OFS_MouseX).ToString();
	}

	//Retrieve Mouse Y Position
	static String^ getMousePosY() {
		return ReadMultiPointerSigned(InputBase, 2, OFS_MouseLocation, OFS_MouseY).ToString();
	}

	//Retrieve Mouse Animation
	static int getMouseAnimation() {
		return ReadPointer(InputBase, OFS_MouseAnimation);
	}
	
	//Retrieve Char Animation
	static String^ getCharAnimation() {
		return ReadPointerSignedInt(UserLocalBase, OFS_CharAnimation).ToString();
	}

	//Retrieve Char Foothold
	static String^ getCharFoothold() {
		return ReadPointerSignedInt(UserLocalBase, OFS_Foothold).ToString();
	}

	//Retrieve Attack Count
	static String^ getAttackCount() {
		return ReadPointerSignedInt(UserLocalBase, OFS_AttackCount).ToString();
	}

	//Retrieve Buff Count
	static String^ getBuffCount() {
		return (*(ULONG*)OFS_BuffCount).ToString();
	}

	//Retrieve Breath Count
	static String^ getBreathCount() {
		return ReadPointerSignedInt(UserLocalBase, OFS_Breath).ToString();
	}

	//Retrieve People Count
	static String^ getPeopleCount() {
		return ReadPointerSignedInt(UserPoolBase, OFS_mUserRemote_uCount).ToString();
	}

	//Retrieve Mob Count
	static String^ getMobCount() {
		return ReadPointerSignedInt(MobPoolBase, OFS_mMob_uCount).ToString();
	}

	//Retrieve Drop Count
	static String^ getDropCount() {
		return ReadPointerSignedInt(DropPoolBase, OFS_mDrop_uCount).ToString();
	}

	//Retrieve Portal Count
	static String^ getPortalCount() {
		return ReadPointerSignedInt(PortalListBase, OFS_PortalCount).ToString();
	}

	//Retrieve NPC Count
	static String^ getNPCCount() {
		return ReadPointerSignedInt(NpcPoolBase, OFS_mNpc_uCount).ToString();
	}
};

namespace HelperFuncs 
{
	static void SetMapleWindowToForeground() {
		SetForegroundWindow(GlobalVars::mapleWindow);
	}

	static RECT GetMapleWindowRect() {
		RECT msRect;
		GetWindowRect(GlobalVars::mapleWindow, &msRect);

		return  msRect;
	}

	static bool IsInGame() {
		const int mapID = Convert::ToInt32(PointerFuncs::getMapID());

		if (!mapID == 0) //&& !PointerFuncs::getCharName()->Equals("CharName")
			return true;

		return false;
	}

	static bool ValidToAttack() {
		const int attCnt = Convert::ToInt32(PointerFuncs::getAttackCount());

		// check for weapon and ammo
		if (!(attCnt > 99) && IsInGame()) //!UsingBuff
			return true;

		return false;
	}

	static bool ValidToLoot() {
		const int pplCnt = Convert::ToInt32(PointerFuncs::getPeopleCount());

		if (!(pplCnt > 0) && IsInGame())
			return true;

		return false;
	}

	// Check if item count > 50 and AutoLoot is Checked
	static bool IsInventoryFull() {
		const int dropCnt = Convert::ToInt32(PointerFuncs::getDropCount());
		// TODO: check if looting
		if (dropCnt >= 100) { 
			Log::WriteLineToConsole("INVENTORY IS FULL!");
			return true;			
		}
		return false;
	}
}

// Assumes trade UI open and maplewindow is in foreground
// These mouse pos should be absolute so it will work when the window is at 800x600 at to left corner
static void SellAllEQPByMouse() {
	const int EQUIP_SLOTS = 186; //actually this depends on server settings, can be extended ingame via CS
	MouseInput::Mouse mouse;

	Log::WriteLineToConsole("Setting Maplestory to foreground ...");
	HelperFuncs::SetMapleWindowToForeground();
	Log::WriteLineToConsole("Moving mouse to UI frame ...");
	// move to trade UI
	mouse.moveTo(420, 190, true, false);
	Sleep(1400 + rand() % 280);
	Log::WriteLineToConsole("Dragging UI frame bottom ...");
	// click and drag to bottom
	mouse.leftDragClickTo(420, 255);
	Sleep(1400 + rand() % 280);
	Log::WriteLineToConsole("Moving mouse to Ok button ...");
	// move to top item where "OK" button is now located
	mouse.moveTo(442, 357, false, false);
	Sleep(1400 + rand() % 280);
	// sell items by one
	for (int i = 1; i < EQUIP_SLOTS; i++) {
		Log::WriteLineToConsole("Double cliking to sell items ... times: " + i);
		mouse.doubleLeftClick();
		Sleep(80 + rand() % 20);
	}
	Log::WriteLineToConsole("Closing trade UI ... ");
	Sleep(1400 + rand() % 280);
	// send close trade packet
	//SendPacket("3D 00 03");	incomplete :/
}

// TODO: find NPC in NpcPool -> get its position/ID -> teleport before it -> send open trade packet
static void SellAllAtEquipMapId(int mapID) {
	if (mapID == 220050300) { // Ludi-Path of time 
		Log::WriteLineToConsole("Were at Ludi Path of Time ...");
		Log::WriteLineToConsole("Teleporting close to NPC ...");
		Teleport(-203, 2922);
		Sleep(200 + rand() % 120);
		Log::WriteLineToConsole("Opening trade UI ...");
		// Send open trade packet
		String^ openPacket;
		array<BYTE>^ openHeader = gcnew array<BYTE> { 0x3A, 0x00 };
		array<BYTE>^ grocerData = gcnew array<BYTE> { 0xBD, 0x35, 0x00, 0x00, 0x1D, 0xFF, 0x6A, 0x0B };
		writeBytes(openPacket, openHeader);
		writeBytes(openPacket, grocerData);
		SendPacket(openPacket);
		Sleep(600 + rand() % 280);

		//Try selling items by mouse
		SellAllEQPByMouse();
	}
	else if (mapID == 220000001) { // Ludibridum Weapon Store	
		Log::WriteLineToConsole("Were at Ludi Path of Time ...");
		Log::WriteLineToConsole("Teleporting close to NPC ...");
		Log::WriteLineToConsole("Opening trade UI ...");
		// Send open trade packet
		//170,155 tradeUI topLeftCorner
		//630,490 tradeUI bottomRightCorner
		String^ openPacket;
		array<BYTE>^ openHeader = gcnew array<BYTE> { 0x3A, 0x00 };
		array<BYTE>^ weaponSeller = gcnew array<BYTE> { 0x03, 0xCA, 0x9A, 0x3B, 0x83, 0xFF, 0x8D, 0x00 };
		array<BYTE>^ armorSeller = gcnew array<BYTE> { 0x02, 0xCA, 0x9A, 0x3B, 0x83, 0xFF, 0x8D, 0x00 };
		writeBytes(openPacket, openHeader);
		writeBytes(openPacket, weaponSeller);
		SendPacket(openPacket);
		Sleep(600 + rand() % 280);

		/*String^ chngMapPacket;
		BYTE portals;
		int mapID;
		String portalLabel;
		BYTE ukwn;
		bool wheel;*/
		// SendPacket("26 00 00 FF FF FF FF 07 00 74 6F 77 65 72 30 30 AD FF 1D 00 00 00 00") ludi->terrace hall
		// SendPacket("26 00 00 FF FF FF FF 05 00 74 6F 70 30 30 7A FF 25 FF 00 00 00") terrace hall->ludi
		//Try selling items by mouse
		SellAllEQPByMouse();
		//SendPacket("26 00 00 FF FF FF FF 05 00 6F 75 74 30 30 59 FF 67 00 00 00 00"); // ludi->store
		//SendPacket("26 00 00 FF FF FF FF 04 00 69 6E 30 31 BA 05 5B FD 00 00 00");    // store->ludi
	};
}

//TODO: the portalname,x,y,targetmap and its name, can be obtained either from client or WZ	
//TODO: send keystroke
//TODO: chngMap packet needs some parsing
static void RushToSellFromTerraceHall(bool packet, bool reverse) {
	if (reverse) {
		SendPacket("26 00 00 FF FF FF FF 04 00 69 6E 30 31 BA 05 5B FD 00 00 00"); // store->ludi
		Sleep(600 + rand() % 280);
		SendPacket("26 00 00 FF FF FF FF 07 00 74 6F 77 65 72 30 30 AD FF 1D 00 00 00 00"); // ludi->terrace hall
		Sleep(600 + rand() % 280);
	}

	const int pt1X = -134;
	const int pt1Y = -219;
	const int pt1tm = 220000000; // LUDI
	Teleport(pt1X, pt1Y);
	Sleep(1400 + rand() % 280);
	const int curCharX = Convert::ToInt32(PointerFuncs::getCharPosX());
	const int curCharY = Convert::ToInt32(PointerFuncs::getCharPosY());
	Log::WriteLineToConsole("curCharX: " + curCharX + ":" + "curCharY" + curCharY);
	//if (curCharX == pt1X && curCharY == pt1Y) { // at portal send packet or key up 
		SendPacket("26 00 00 FF FF FF FF 05 00 74 6F 70 30 30 7A FF 25 FF 00 00 00"); // terrace hall->ludi
		Sleep(1400 + rand() % 280);
		const int curCharMapID = Convert::ToInt32(PointerFuncs::getMapID());

		if (curCharMapID == pt1tm) {
			const int pt2X = 1466;
			const int pt2Y = -677;
			const int pt2tm = 220000001; // LUDI wep store
			Teleport(pt2X, pt2Y);
			Sleep(3400 + rand() % 280);
			const int curCharX2 = Convert::ToInt32(PointerFuncs::getCharPosX());
			const int curCharY2 = Convert::ToInt32(PointerFuncs::getCharPosY());

			//if (curCharX2 == pt2X && curCharY2 == pt2Y) { // at portal send packet or key up 
				SendPacket("26 00 00 FF FF FF FF 05 00 6F 75 74 30 30 59 FF 67 00 00 00 00"); // ludi-> wpn store
				Sleep(1400 + rand() % 280);
				const int curCharMapID2 = Convert::ToInt32(PointerFuncs::getMapID());

				//TODO: at destination check for npc nearby
				if (curCharMapID2 == pt2tm) {		
					SellAllAtEquipMapId(curCharMapID2);
				}
			//}
		}
	//}
}

#include <unordered_map>
static std::unordered_map<std::string, int> InitializeUseItems() {
	// Initialize items
	std::unordered_map<std::string, int> useItems({
	{ "Red Potion", 2000000 },
	{ "Orange Potion", 2000001 },
	{ "White Potion", 2000002 },
	{ "Blue Potion", 2000003 },
	{ "Elixir", 2000004 },
	{ "Power Elixir", 2000005 },
	{ "Mana Elixir", 2000006 },
	{ "Red Pill", 2000007 },
	{ "Orange Pill", 2000008 },
	{ "White Pill", 2000009 },
	{ "Blue Pill", 2000010 },
	{ "Mana Elixir Pill", 2000011 },
	{ "Elixir", 2000012 },
	{ "Red Potion for Beginners", 2000013 },
	{ "Blue Potion for Beginners", 2000014 },
	{ "Orange Potion for Beginners", 2000015 },
	{ "White Potion", 2000016 },
	{ "Blue Potion", 2000017 },
	{ "Mana Elixir", 2000018 },
	{ "Power Elixir", 2000019 },
	{ "Red Potion for Noblesse", 2000020 },
	{ "Blue Potion for Noblesse", 2000021 },
	{ "Special Rien Red Potion", 2000022 },
	{ "Special Rien Blue Potion", 2000023 },
	{ "Watermelon", 2001000 },
	{ "Ice Cream Pop", 2001001 },
	{ "Red Bean Sundae", 2001002 },
	{ "Dexterity Potion", 2002000 },
	{ "Speed Potion", 2002001 },
	{ "Magic Potion", 2002002 },
	{ "Wizard Potion", 2002003 },
	{ "Warrior Potion", 2002004 },
	{ "Sniper Potion", 2002005 },
	{ "Warrior Pill", 2002006 },
	{ "Magic Pill", 2002007 },
	{ "Sniper Pill", 2002008 },
	{ "Dexterity Pill", 2002009 },
	{ "Speed Pill", 2002010 },
	{ "Pain Reliever", 2002011 },
	{ "Elixir", 2002012 },
	{ "Power Elixir", 2002013 },
	{ "Iron Body Medicine", 2002014 },
	{ "Elpam Elixir", 2002015 },
	{ "Thief Elixir", 2002016 },
	{ "Warrior Elixir", 2002017 },
	{ "Wizard Elixir", 2002018 },
	{ "Archer Elixir", 2002019 },
	{ "Mana Bull", 2002020 },
	{ "Honster", 2002021 },
	{ "Ginseng Root", 2002022 },
	{ "Ginger Ale", 2002023 },
	{ "Sorcerer Elixir", 2002024 },
	{ "Barbarian Elixir", 2002025 },
	{ "Ginger Ale", 2002026 },
	{ "Stirge Signal", 2002027 },
	{ "T-1337 Supercharger", 2002028 },
	{ "Ridley's Scroll of Defense", 2002029 },
	{ "Angelic Steps", 2002030 },
	{ "Apple", 2010000 },
	{ "Meat", 2010001 },
	{ "Egg", 2010002 },
	{ "Orange", 2010003 },
	{ "Lemon", 2010004 },
	{ "Honey", 2010005 },
	{ "Pot of Honey", 2010006 },
	{ "Roger's Apple", 2010007 },
	{ "Green Apple", 2010009 },
	{ "Poisonous Mushroom", 2011000 },
	{ "Drake's Blood", 2012000 },
	{ "Fairy's Honey", 2012001 },
	{ "Sap of Ancient Tree", 2012002 },
	{ "Drake's Meat", 2012003 },
	{ "Purified Honey", 2012004 },
	{ "Angel Apple", 2012005 },
	{ "Angel Lemon", 2012006 },
	{ "Unripe Onyx Apple", 2012008 },
	{ "Salad", 2020000 },
	{ "Fried Chicken", 2020001 },
	{ "Cake", 2020002 },
	{ "Pizza", 2020003 },
	{ "Hamburger", 2020004 },
	{ "Hot Dog", 2020005 },
	{ "Hot Dog Supreme", 2020006 },
	{ "Dried Squid", 2020007 },
	{ "Fat Sausage", 2020008 },
	{ "Orange Juice", 2020009 },
	{ "Grape Juice", 2020010 },
	{ "W Ramen", 2020011 },
	{ "Melting Cheese", 2020012 },
	{ "Reindeer Milk", 2020013 },
	{ "Sunrise Dew", 2020014 },
	{ "Sunset Dew", 2020015 },
	{ "Cheesecake", 2020016 },
	{ "Strawberry Cream Cake", 2020017 },
	{ "Chocolate Cream Cake", 2020018 },
	{ "Chocolate Cake", 2020019 },
	{ "Wedding Cake", 2020020 },
	{ "Nemi's Lunch Box", 2020021 },
	{ "White Chocolate", 2020022 },
	{ "Dark Chocolate", 2020023 },
	{ "Chocolate Basket", 2020024 },
	{ "Pineapple Candy", 2020025 },
	{ "Strawberry Candy", 2020026 },
	{ "Candy Basket", 2020027 },
	{ "Chocolate", 2020028 },
	{ "Corn", 2020029 },
	{ "Roasted Turkey", 2020030 },
	{ "Coca_Cola", 2020031 },
	{ "Birthday Cake", 2020032 },
	{ "Pure Water", 2022000 },
	{ "Red Bean Porridge", 2022001 },
	{ "Cider", 2022002 },
	{ "Unagi", 2022003 },
	{ "Song Pyun", 2022004 },
	{ "Han Gwa", 2022005 },
	{ "Rice-Cake Soup", 2022006 },
	{ "Triangular Sushi(plum)", 2022007 },
	{ "Triangular Sushi(salmon)", 2022008 },
	{ "Triangular Sushi(bonito)", 2022009 },
	{ "Triangular Sushi(pollack)", 2022010 },
	{ "Triangular Sushi(mushroom)", 2022011 },
	{ "Sushi(tuna)", 2022012 },
	{ "Sushi(salmon)", 2022013 },
	{ "Dango", 2022014 },
	{ "Mushroom Miso Ramen", 2022015 },
	{ "Maple Special Bento", 2022016 },
	{ "Ramen", 2022017 },
	{ "Kinoko Ramen(roasted pork)", 2022018 },
	{ "Kinoko Ramen(pig head)", 2022019 },
	{ "Kinoko Ramen(salt)", 2022020 },
	{ "Fish Cake(skewer)", 2022021 },
	{ "Fish Cake(dish)", 2022022 },
	{ "Tri-colored Dango", 2022023 },
	{ "Takoyaki (Octopus Ball)", 2022024 },
	{ "Takoyaki (jumbo)", 2022025 },
	{ "Yakisoba", 2022026 },
	{ "Yakisoba (x2)", 2022027 },
	{ "Valentine Chocolate (Dark)", 2022028 },
	{ "Valentine Chocolate (Strawberry)", 2022029 },
	{ "Valentine Chocolate (White)", 2022030 },
	{ "Cookie", 2022031 },
	{ "Marshmallow", 2022032 },
	{ "Candy", 2022033 },
	{ "Zong Zi", 2022034 },
	{ "Maple Cola", 2022035 },
	{ "Candy Basket", 2022036 },
	{ "Pink Rice Cake", 2022037 },
	{ "Rice Cookie", 2022038 },
	{ "Nependeath's Honey", 2022039 },
	{ "Air Bubble", 2022040 },
	{ "Fried shrimp", 2022041 },
	{ "Cookie", 2022042 },
	{ "Fruity Candy", 2022043 },
	{ "New Year Rice Cake", 2022044 },
	{ "New Year Lunchbox", 2022045 },
	{ "Seaweed", 2022046 },
	{ "Cooked Sea Bream", 2022047 },
	{ "New Year Rice Soup", 2022048 },
	{ "Steamed Crab", 2022049 },
	{ "Roasted pork", 2022050 },
	{ "Buckwheat paste", 2022051 },
	{ "Rice Wine", 2022052 },
	{ "Jujube", 2022053 },
	{ "Pear", 2022054 },
	{ "Persimmon", 2022055 },
	{ "Chestnut", 2022056 },
	{ "Tofu", 2022057 },
	{ "Dumpling", 2022058 },
	{ "Lotus Perfume", 2022060 },
	{ "Oriental Perfume", 2022061 },
	{ "Chrysanthemum Perfume", 2022062 },
	{ "Corn Stick", 2022063 },
	{ "Fruit Stick", 2022064 },
	{ "Yellow Easter Egg", 2022065 },
	{ "Green Easter Egg", 2022066 },
	{ "Yellow Cider", 2022068 },
	{ "Red Cider", 2022069 },
	{ "Congrats from GM", 2022070 },
	{ "Korean Warrior", 2022071 },
	{ "Forza Corea", 2022072 },
	{ "A Prayer for Victory", 2022073 },
	{ "Oolleung Squid", 2022074 },
	{ "Mini Coke", 2022075 },
	{ "Coke Pill", 2022076 },
	{ "Coke Lite Pill", 2022077 },
	{ "Coke Zero Pill", 2022078 },
	{ "Barbecue", 2022079 },
	{ "Red Fruit", 2022086 },
	{ "Black Fruit", 2022087 },
	{ "Blue Fruit", 2022088 },
	{ "Baby Dragon Food", 2022089 },
	{ "Blessing from Wonky the Fairy", 2022090 },
	{ "Blessing from Wonky the Fairy", 2022091 },
	{ "Blessing from Wonky the Fairy", 2022092 },
	{ "Blessing from Wonky the Fairy", 2022093 },
	{ "Chicken Soup", 2022094 },
	{ "Fried Chicken", 2022096 },
	{ "Chun Gwon", 2022097 },
	{ "Bubble Gum", 2022098 },
	{ "HP up", 2022099 },
	{ "Song Pyun", 2022100 },
	{ "Han Gwa", 2022101 },
	{ "Massage Oil", 2022102 },
	{ "Thai Cookie", 2022103 },
	{ "Green Malady's Candy", 2022105 },
	{ "Red Malady's Candy", 2022106 },
	{ "Blue Malady's Candy", 2022107 },
	{ "Horntail Squad : Victory", 2022108 },
	{ "The Breath of Nine Spirit", 2022109 },
	{ "Baby Witch", 2022112 },
	{ "Pumpkin Pie", 2022113 },
	{ "Enchanted Apple Crisp", 2022114 },
	{ "Peach", 2022116 },
	{ "Maple Syrup", 2022117 },
	{ "Admin's Congrats", 2022118 },
	{ "Tree Ornament", 2022119 },
	{ "Christmas Melon", 2022120 },
	{ "Gelt Chocolate", 2022121 },
	{ "Banana Graham Pie", 2022123 },
	{ "Magic of Kasandra", 2022124 },
	{ "Increase in Weapon Defense", 2022125 },
	{ "Increase in Magic Defense", 2022126 },
	{ "Increase in Accuracy", 2022127 },
	{ "Increase in Avoidablility", 2022128 },
	{ "Increase in Attack", 2022129 },
	{ "Blossom Juice", 2022130 },
	{ "Ginseng Concentrate", 2022131 },
	{ "Bellflower Concentrate", 2022132 },
	{ "Mind & Heart Medicine", 2022142 },
	{ "Mastery Medicine", 2022143 },
	{ "Body & Physics Medicine", 2022144 },
	{ "Canned Peach", 2022145 },
	{ "Peach Juice", 2022146 },
	{ "Bellflower Medicine Soup", 2022147 },
	{ "Pill of Tunnel Vision", 2022148 },
	{ "Pill of Intelligence", 2022149 },
	{ "Slithering Balm", 2022150 },
	{ "Cassandra's Magic", 2022151 },
	{ "Cassandra's Magic", 2022152 },
	{ "Happy birthday", 2022153 },
	{ "Petit Rose", 2022154 },
	{ "Desert Mist", 2022155 },
	{ "Black Bean Noodle", 2022156 },
	{ "Carnival Point 1", 2022157 },
	{ "Carnival Point 2", 2022158 },
	{ "Carnival Point 3", 2022159 },
	{ "Party Mana Elixir", 2022160 },
	{ "Party Elixir", 2022161 },
	{ "Party Power Elixir", 2022162 },
	{ "Party All Cure Potion", 2022163 },
	{ "Mini Cube of Darkness", 2022164 },
	{ "Cube of Darkness", 2022165 },
	{ "Stunner", 2022166 },
	{ "White Potion", 2022174 },
	{ "Elixir", 2022175 },
	{ "Power Elixir", 2022176 },
	{ "Mana Elixir", 2022177 },
	{ "All-Cure Potion", 2022178 },
	{ "Onyx Apple", 2022179 },
	{ "Amorian Rice Cookie", 2022180 },
	{ "Victoria's Amorian Basket", 2022181 },
	{ "Crystalized Pineapple Chew", 2022182 },
	{ "Flower Shower", 2022183 },
	{ "Maple BBQ", 2022184 },
	{ "Fireworks", 2022185 },
	{ "Soft White Bun", 2022186 },
	{ "Cassandra's Magic", 2022187 },
	{ "Grilled Cheese", 2022189 },
	{ "Cherry Pie", 2022190 },
	{ "Supreme Pizza", 2022191 },
	{ "Waffle", 2022192 },
	{ "Merlin Orb", 2022193 },
	{ "Leaf Crystal", 2022194 },
	{ "Mapleade", 2022195 },
	{ "Wedding Bouquet", 2022196 },
	{ "Wedding Bouquet", 2022197 },
	{ "Russellon's Pills", 2022198 },
	{ "Russellon's Potion", 2022199 },
	{ "Wedding Bouquet", 2022200 },
	{ "Laksa", 2022203 },
	{ "Hokkien Mee", 2022204 },
	{ "Carrot Cake", 2022205 },
	{ "Chicken Rice", 2022206 },
	{ "Satay", 2022207 },
	{ "Guava", 2022208 },
	{ "Rambutan", 2022209 },
	{ "Dragon Fruit", 2022210 },
	{ "Durian", 2022211 },
	{ "Nasi Lemak", 2022212 },
	{ "Roti Prata", 2022213 },
	{ "Pepper Crab", 2022214 },
	{ "Chili Crab", 2022215 },
	{ "Russellon's Potion", 2022224 },
	{ "Russellon's Potion", 2022225 },
	{ "Russellon's Potion", 2022226 },
	{ "Russellon's Potion", 2022227 },
	{ "Russellon's Potion", 2022228 },
	{ "MesoGears Ring", 2022238 },
	{ "Cassandra's Magic", 2022239 },
	{ "Cassandra's Magic", 2022240 },
	{ "Edmund's Special Brew", 2022242 },
	{ "Sophilia's Necklace", 2022243 },
	{ "Smore", 2022244 },
	{ "Heartstopper", 2022245 },
	{ "Pumpkin Taffy", 2022246 },
	{ "Red Gummy Slime", 2022247 },
	{ "Green Gummy Slime", 2022248 },
	{ "Purple Gummy Slime", 2022249 },
	{ "Orange Gummy Slime", 2022250 },
	{ "Maple Pop", 2022251 },
	{ "Tae Roon's Note", 2022252 },
	{ "Mushroom Candy", 2022253 },
	{ "Pumpkin Pieces", 2022255 },
	{ "Halloween Candy", 2022256 },
	{ "Power of the Glowing Rock", 2022257 },
	{ "Coconut Juice", 2022258 },
	{ "Attack Crystal", 2022259 },
	{ "Accuracy Crystal", 2022260 },
	{ "Stuffing Scoop", 2022261 },
	{ "Cranberry Sauce", 2022262 },
	{ "Mashed Potato", 2022263 },
	{ "Gravy", 2022264 },
	{ "Snowing Fishbread", 2022265 },
	{ "Power Punch", 2022266 },
	{ "Wing of the Wind", 2022267 },
	{ "Crazy Skull", 2022268 },
	{ "Shield", 2022269 },
	{ "Maplemas Ham", 2022271 },
	{ "Smoken Salmon", 2022272 },
	{ "Ssiws Cheese", 2022273 },
	{ "Sugar-Coated Olives", 2022274 },
	{ "Caramel Onion", 2022275 },
	{ "Chocolate Wafers", 2022276 },
	{ "Sunblock", 2022277 },
	{ "Lump of Coal", 2022278 },
	{ "Snow Cake Piece", 2022279 },
	{ "A Flurry of Snow", 2022280 },
	{ "Chinese Firecrackers", 2022281 },
	{ "Naricain's Demon Elixir", 2022282 },
	{ "Subani's Mystic Cauldron", 2022283 },
	{ "Barricade Booster", 2022284 },
	{ "Sweet Heart", 2022285 },
	{ "Power Scream", 2022296 },
	{ "Party Bear", 2022302 },
	{ "Taru Face Paint", 2022305 },
	{ "Primal Brew", 2022306 },
	{ "Spirit Herbs", 2022307 },
	{ "Jungle Juice", 2022308 },
	{ "Treasure Hunt Note", 2022309 },
	{ "Chocolate Cream Cupcake", 2022310 },
	{ "Big Cream Puff", 2022311 },
	{ "Fish Net with a Catch", 2022323 },
	{ "Big Belly Fish", 2022324 },
	{ "Blessing of the Forest", 2022326 },
	{ "Agent O's Encouragement", 2022332 },
	{ "Agent O's Encouragement", 2022333 },
	{ "Baby Chick Cookie", 2022335 },
	{ "Secret Box", 2022336 },
	{ "Sorcerer's Potion", 2022337 },
	{ "VitroJuice", 2022338 },
	{ "NitroJuice", 2022339 },
	{ "BlastroJuice", 2022340 },
	{ "ElectroJuice", 2022341 },
	{ "MegaJuice", 2022342 },
	{ "GigaJuice", 2022343 },
	{ "JigaJuice", 2022344 },
	{ "The Energizer Drink", 2022345 },
	{ "Fire Grill Skewer", 2022352 },
	{ "Tick-Tock's Egg", 2022354 },
	{ "Cronos' Egg", 2022355 },
	{ "Sweet Rice Cake", 2022356 },
	{ "Sweet Rice Cake", 2022357 },
	{ "Sweet Rice Cake", 2022358 },
	{ "Increases Physical Attack Rat.", 2022359 },
	{ "Increases Magic Attack Rate.", 2022360 },
	{ "Increases Physical Defense Rate.", 2022361 },
	{ "Increases Magic Defense Rate.", 2022362 },
	{ "Increases Accuracy", 2022363 },
	{ "Increases Avoidability", 2022364 },
	{ "Increases Speed", 2022365 },
	{ "Increases Max HP", 2022366 },
	{ "Increases Max MP", 2022367 },
	{ "Increases Physical Attack Rate", 2022368 },
	{ "Increases Magic Attack Rate", 2022369 },
	{ "Increases Physical Defense Rate", 2022370 },
	{ "Increases Magic Defense Rate", 2022371 },
	{ "Increases Accuracy", 2022372 },
	{ "Increases Avoidability", 2022373 },
	{ "Increases Speed", 2022374 },
	{ "Increases MaxHP", 2022375 },
	{ "Increases Max MP", 2022376 },
	{ "Increases Physical Attack Rate", 2022377 },
	{ "Increases Magic Attack Rate", 2022378 },
	{ "Increases Physical Defense Rate", 2022379 },
	{ "Increases Magic Defense Rate", 2022380 },
	{ "Increases Accuracy", 2022381 },
	{ "Increases Avoidability", 2022382 },
	{ "Increases Speed", 2022383 },
	{ "Increases Max HP", 2022384 },
	{ "Increases Max MP", 2022385 },
	{ "Increases Physical Attack Rate", 2022386 },
	{ "Increases Magic Attack Rate", 2022387 },
	{ "Increases Physical Defense Rate", 2022388 },
	{ "Increases Magic Defense Rate", 2022389 },
	{ "Increases Accuracy", 2022390 },
	{ "Increases Avoidability", 2022391 },
	{ "Increases Speed", 2022392 },
	{ "Increases Max HP", 2022393 },
	{ "Increases Max MP", 2022394 },
	{ "Increases Physical Attack Rate", 2022395 },
	{ "Increases Magic Attack Rate", 2022396 },
	{ "Increases Physical Defense Rate", 2022397 },
	{ "Increases Magic Defense Rate", 2022398 },
	{ "Increases Accuracy", 2022399 },
	{ "Increases Avoidability", 2022400 },
	{ "Increases Speed", 2022401 },
	{ "Increases Max HP", 2022402 },
	{ "Increases Max MP", 2022403 },
	{ "Increases Physical Attack Rate", 2022404 },
	{ "Increases Magic Attack Rate", 2022405 },
	{ "Increases Physical Defense Rate", 2022406 },
	{ "Increases Magic Defense Rate", 2022407 },
	{ "Increases Accuracy", 2022408 },
	{ "Increases Avoidability", 2022409 },
	{ "Increases Speed", 2022410 },
	{ "Increases Max HP", 2022411 },
	{ "Increases Max MP", 2022412 },
	{ "Increases Physical Attack Rate", 2022413 },
	{ "Increases Magic Attack Rate", 2022414 },
	{ "Increases Physical Defense Rate", 2022415 },
	{ "Increases Magic Defense Rate", 2022416 },
	{ "Increases Accuracy", 2022417 },
	{ "Increases Avoidability", 2022418 },
	{ "Increases Speed", 2022419 },
	{ "Increases Max HP", 2022420 },
	{ "Increases Max MP", 2022421 },
	{ "Small Stories", 2022422 },
	{ "Gaga's Appreciation", 2022423 },
	{ "Gaga's Appreciation", 2022424 },
	{ "Mysterious Box", 2022428 },
	{ "Protective Shield", 2022429 },
	{ "Mu Lung Dojo Mana Elixir", 2022430 },
	{ "Mu Lung Dojo Elixir", 2022431 },
	{ "Mu Lung Dojo Power Elixir", 2022432 },
	{ "Mu Lung Dojo Cure-All Medicine", 2022433 },
	{ "Warm and Fuzzy Winter", 2022434 },
	{ "Holiday Buff", 2022436 },
	{ "Holiday Buff", 2022437 },
	{ "Holiday Buff", 2022438 },
	{ "Elixir of Darkness", 2022439 },
	{ "Gold Dust", 2022440 },
	{ "Adonis Cauldron", 2022441 },
	{ "Maze Reward", 2022442 },
	{ "Fireworks", 2022443 },
	{ "Mihile's Blessing", 2022444 },
	{ "Oz's Blessing", 2022445 },
	{ "Irena's Blessing", 2022446 },
	{ "Eckhart's Blessing", 2022447 },
	{ "Hawkeye's Blessing", 2022448 },
	{ "Pink Bean Squad : Victory", 2022449 },
	{ "EXP Increase(S)", 2022450 },
	{ "EXP Increase(M)", 2022451 },
	{ "EXP Increase(L)", 2022452 },
	{ "Fireworks", 2022453 },
	{ "Cygnus's Blessing", 2022454 },
	{ "Happy New Year!", 2022455 },
	{ "Elixir", 2022456 },
	{ "Power Elixir", 2022457 },
	{ "Shinsoo's Blessing", 2022458 },
	{ "Cassandra's Reward 1", 2022459 },
	{ "Cassandra's Reward 2", 2022460 },
	{ "Cassandra's Reward 3", 2022461 },
	{ "Cassandra's Reward 4", 2022462 },
	{ "Cassandra's Reward 5", 2022463 },
	{ "Heartpounding Box", 2022465 },
	{ "Heartpounding Box", 2022466 },
	{ "Heartpounding Box", 2022467 },
	{ "Heartpounding Box", 2022468 },
	{ "Chicken Kapitan", 2022476 },
	{ "Mee Siam", 2022477 },
	{ "Rojak", 2022478 },
	{ "Kangkung belacan", 2022479 },
	{ "Kuih", 2022480 },
	{ "Mysterious Maple", 2022481 },
	{ "Pigmy's Wings", 2022482 },
	{ "Cassandra's Star", 2022496 },
	{ "Point Improvement Treasure Chest", 2022499 },
	{ "Point Increase Treasure Chest", 2022500 },
	{ "Geppetto's Writing Analysis", 2022501 },
	{ "Hero's Gladius", 2022502 },
	{ "Golden Pig's Shiny Egg", 2022503 },
	{ "Golden Pig's Shiny Egg", 2022504 },
	{ "Golden Pig's Shiny Egg", 2022505 },
	{ "Golden Pig's Shiny Egg", 2022506 },
	{ "Golden Pig's Shiny Egg", 2022507 },
	{ "Golden Pig's Shiny Egg", 2022508 },
	{ "Golden Pig's Shiny Egg", 2022509 },
	{ "Golden Pig's Shiny Egg", 2022510 },
	{ "Golden Pig's Shiny Egg", 2022511 },
	{ "Golden Pig's Shiny Egg", 2022512 },
	{ "Golden Pig's Shiny Egg", 2022513 },
	{ "Golden Pig's Dazzling Egg", 2022514 },
	{ "Golden Pig's Dazzling Egg", 2022515 },
	{ "Golden Pig's Dazzling Egg", 2022516 },
	{ "Golden Pig's Dazzling Egg", 2022517 },
	{ "Golden Pig's Dazzling Egg", 2022518 },
	{ "Golden Pig's Dazzling Egg", 2022519 },
	{ "Golden Pig's Dazzling Egg", 2022520 },
	{ "Golden Pig's Dazzling Egg", 2022521 },
	{ "Golden Pig's Dazzling Egg", 2022522 },
	{ "Golden Pig's Dazzling Egg", 2022523 },
	{ "Golden Pig's Dazzling Egg", 2022524 },
	{ "Azalea", 2022526 },
	{ "Forsythia", 2022527 },
	{ "Clover", 2022528 },
	{ "Meaning of Azaleas", 2022529 },
	{ "Meaning of Forsythias", 2022530 },
	{ "Meaning of Clovers", 2022531 },
	{ "Underground Temple's Seal", 2022536 },
	{ "Gladius' Strength", 2022537 },
	{ "Red Easter Egg", 2022538 },
	{ "Cry of a Little Lamb", 2022539 },
	{ "Danger Escape", 2022540 },
	{ "Self Protection", 2022541 },
	{ "Little Lamb's Surprise Attack", 2022542 },
	{ "Great Confusion", 2022543 },
	{ "White Elixir", 2022544 },
	{ "Dynamite Drink EX", 2022545 },
	{ "Energy Drink", 2022546 },
	{ "Sound of the Sheep's Bells", 2022547 },
	{ "Sound of the Wolf's Bells", 2022548 },
	{ "Wolf's Threat", 2022549 },
	{ "Sheep Ranch Golden ? Egg", 2022550 },
	{ "6th Anniversary Gift Box", 2022552 },
	{ "Crackers's Buff", 2022553 },
	{ "Independence Day Firecracker 1", 2022554 },
	{ "Independence Day Firecracker 2", 2022555 },
	{ "Independence Day Firecracker 3", 2022556 },
	{ "Artifact Hunt Encouragement Buff", 2022562 },
	{ "Artifact Hunt Encouragement Buff", 2022563 },
	{ "Aran Paper Box", 2022564 },
	{ "King Pepe Warrior Weapon Box", 2022570 },
	{ "King Pepe Magician Weapon Box", 2022571 },
	{ "King Pepe Bowman Weapon Box", 2022572 },
	{ "King Pepe Thief Weapon Box", 2022573 },
	{ "King Pepe Pirate Weapon Box", 2022574 },
	{ "King Pepe Warrior Armor Box", 2022575 },
	{ "King Pepe Magician Armor Box", 2022576 },
	{ "King Pepe Bowman Armor Box", 2022577 },
	{ "King Pepe Thief Armor Box", 2022578 },
	{ "King Pepe Pirate Armor Box", 2022579 },
	{ "King Pepe Warrior Box", 2022580 },
	{ "King Pepe Magician Box", 2022581 },
	{ "King Pepe Bowman Box", 2022582 },
	{ "King Pepe Thief Box", 2022583 },
	{ "King Pepe Pirate Box", 2022584 },
	{ "Pharaoh's Blessing Lv. 1", 2022585 },
	{ "Pharaoh's Blessing Lv. 2", 2022586 },
	{ "Pharaoh's Blessing Lv. 3", 2022587 },
	{ "Pharaoh's Blessing Lv. 4", 2022588 },
	{ "Pharaoh's Treasure Chest", 2022613 },
	{ "Bingo Gift Box", 2022614 },
	{ "Subway Lost and Found", 2022615 },
	{ "Power Buff Lv. 1", 2022616 },
	{ "Power Buff Lv. 2", 2022617 },
	{ "Pharaoh's Treasure Chest", 2022618 },
	{ "Handmade Sandwich ", 2022620 },
	{ "Tasty Milk", 2022621 },
	{ "Squeezed Juice", 2022622 },
	{ "Seasoned Frog Eggs and Mushrooms", 2022623 },
	{ "Bloody Mushroom Wine", 2022624 },
	{ "Slimy Canape", 2022625 },
	{ "Zingy Kabab", 2022626 },
	{ "Swamp Wrap", 2022627 },
	{ "Rough Leather Steak", 2022628 },
	{ "Witch's Special Stew", 2022629 },
	{ "Rose Scent", 2022631 },
	{ "Freesia Scent", 2022632 },
	{ "Lavender Scent", 2022633 },
	{ "Turkey Leg", 2022634 },
	{ "Return Scroll", 2030000 },
	{ "Return Scroll to Lith Harbor", 2030001 },
	{ "Return Scroll to Ellinia", 2030002 },
	{ "Return Scroll to Perion", 2030003 },
	{ "Return Scroll to Henesys", 2030004 },
	{ "Return Scroll to Kerning City", 2030005 },
	{ "Return Scroll to Sleepywood", 2030006 },
	{ "Return Scroll for Dead Mine", 2030007 },
	{ "Coffee Milk", 2030008 },
	{ "Strawberry Milk", 2030009 },
	{ "Fruit Milk", 2030010 },
	{ "Command Center Warp Capsule", 2030011 },
	{ "Ludibrium Warp Capsule", 2030012 },
	{ "Phyllia's Warp Powder", 2030016 },
	{ "Nautilus Return Scroll", 2030019 },
	{ "Return to New Leaf City Scroll", 2030020 },
	{ "Masked Man's Invitation", 2031000 },
	{ "Studio Invitation", 2031001 },
	{ "Invitation to the Moon", 2031002 },
	{ "Invitation to the Nest", 2031003 },
	{ "Invitation to Ereve", 2031004 },
	{ "Family Studio Photo Coupon", 2031006 },
	{ "Rien Teleport Ticket", 2031008 },
	{ "Richie Gold's Strange Lamp", 2032000 },
	{ "Scroll for Helmet for DEF", 2040000 },
	{ "Scroll for Helmet for DEF", 2040001 },
	{ "Scroll for Helmet for DEF", 2040002 },
	{ "Scroll for Helmet for HP", 2040003 },
	{ "Scroll for Helmet for HP", 2040004 },
	{ "Scroll for Helmet for HP", 2040005 },
	{ "Scroll for Helmet for DEF", 2040006 },
	{ "Scroll for Helmet for HP", 2040007 },
	{ "Dark scroll for Helmet for DEF", 2040008 },
	{ "Dark Scroll for Helmet for DEF", 2040009 },
	{ "Scroll for Helmet for HP", 2040010 },
	{ "Dark Scroll for Helmet for HP", 2040011 },
	{ "Dark Scroll for Helmet for INT", 2040012 },
	{ "Dark Scroll for Helmet for INT", 2040013 },
	{ "Dark Scroll for Helmet for Accuracy", 2040014 },
	{ "Dark Scroll for Helmet for Accuracy", 2040015 },
	{ "Scroll for Helmet for Accuracy", 2040016 },
	{ "Scroll for Helmet for Accuracy", 2040017 },
	{ "Scroll for Helmet for Accuracy", 2040018 },
	{ "Scroll for Helmet for DEF", 2040019 },
	{ "Scroll for Helmet for DEF", 2040020 },
	{ "Scroll for Helmet for MaxHP", 2040021 },
	{ "Scroll for Helmet for MaxHP", 2040022 },
	{ "Scroll for Rudolph's Horn 60%", 2040023 },
	{ "Scroll for Helmet for INT 100%", 2040024 },
	{ "Scroll for Helmet for INT 60%", 2040025 },
	{ "Scroll for Helmet for INT 10%", 2040026 },
	{ "Scroll for Helmet for DEX 100%", 2040027 },
	{ "Scroll for Helmet for DEX 70%", 2040028 },
	{ "Scroll for Helmet for DEX 60%", 2040029 },
	{ "Scroll for Helmet for DEX 30%", 2040030 },
	{ "Scroll for Helmet for DEX 10%", 2040031 },
	{ "Scroll for Helmet for DEF 100%", 2040041 },
	{ "Scroll for Helmet for HP 100%", 2040042 },
	{ "Scroll for Helmet for DEX 65%", 2040043 },
	{ "Scroll for Helmet for DEX 15%", 2040044 },
	{ "Scroll for Helmet for DEF 50%", 2040045 },
	{ "Scroll for Helmet for HP 50%", 2040046 },
	{ "Scroll for Face Accessory for HP", 2040100 },
	{ "Scroll for Face Accessory for HP", 2040101 },
	{ "Scroll for Face Accessory for HP", 2040102 },
	{ "Dark Scroll for Face Accessory for HP", 2040103 },
	{ "Dark Scroll for Face Accessory for HP", 2040104 },
	{ "Scroll for Face Accessory for Avoidability", 2040105 },
	{ "Scroll for Face Accessory for Avoidability", 2040106 },
	{ "Scroll for Face Accessory for Avoidability", 2040107 },
	{ "Dark Scroll for Face Accessory for Avoidability", 2040108 },
	{ "Dark Scroll for Face Accessory for Avoidability", 2040109 },
	{ "Red-Nose STR Bandage 60%", 2040110 },
	{ "Red-Nose DEX Bandage 60%", 2040111 },
	{ "Red-Nose INT Bandage 60%", 2040112 },
	{ "Red-Nose LUK Bandage 60%", 2040113 },
	{ "Red-Nose ATT Bandage 60%", 2040114 },
	{ "Red-Nose Weapon DEF Bandage 60%", 2040115 },
	{ "Red-Nose MP Bandage 60%", 2040116 },
	{ "Red-Nose Magic DEF Bandage 60%", 2040117 },
	{ "Red-Nose Avoidability Bandage 60%", 2040118 },
	{ "Red-Nose Accuracy Bandage 60%", 2040119 },
	{ "Scroll for Eye Accessory for Accuracy", 2040200 },
	{ "Scroll for Eye Accessory for Accuracy", 2040201 },
	{ "Scroll for Eye Accessory for Accuracy", 2040202 },
	{ "Dark Scroll for Eye Accessory for Accuracy", 2040203 },
	{ "Dark Scroll for Eye Accessory for Accuracy", 2040204 },
	{ "Scroll for Eye Accessory for INT", 2040205 },
	{ "Scroll for Eye Accessory for INT", 2040206 },
	{ "Scroll for Eye Accessory for INT", 2040207 },
	{ "Dark Scroll for Eye Accessory for INT", 2040208 },
	{ "Dark Scroll for Eye Accessory for INT", 2040209 },
	{ "Scroll for Earring for INT", 2040300 },
	{ "Scroll for Earring for INT", 2040301 },
	{ "Scroll for Earring for INT", 2040302 },
	{ "Scroll for Earring for INT", 2040303 },
	{ "Dark scroll for Earring for INT", 2040304 },
	{ "Dark scroll for Earring for INT", 2040305 },
	{ "Dark scroll for Earring for DEX", 2040306 },
	{ "Dark scroll for Earring for DEX", 2040307 },
	{ "Dark Scroll for Earrings for DEF", 2040308 },
	{ "Dark Scroll for Earrings for DEF", 2040309 },
	{ "Scroll for Earring for DEF", 2040310 },
	{ "Scroll for Earring for DEF", 2040311 },
	{ "Scroll for Earring for DEF", 2040312 },
	{ "Scroll for Earring for INT", 2040313 },
	{ "Scroll for Earring for INT", 2040314 },
	{ "[4yrAnniv]Scroll for Earring for INT", 2040315 },
	{ "Scroll for Earring for DEX 100%", 2040316 },
	{ "Scroll for Earring for DEX 60%", 2040317 },
	{ "Scroll for Earring for DEX 10%", 2040318 },
	{ "Scroll for Earring for LUK 100%", 2040319 },
	{ "Scroll for Earring for LUK 70%", 2040320 },
	{ "Scroll for Earring for LUK 60%", 2040321 },
	{ "Scroll for Earring for LUK 30%", 2040322 },
	{ "Scroll for Earring for LUK 10%", 2040323 },
	{ "Scroll for Earring for HP 100%", 2040324 },
	{ "Scroll for Earring for HP 70%", 2040325 },
	{ "Scroll for Earring for HP 60%", 2040326 },
	{ "Scroll for Earring for HP 30%", 2040327 },
	{ "Scroll for Earring for HP 10%", 2040328 },
	{ "Scroll for Earring for DEX 10%", 2040329 },
	{ "Scroll for Earring for INT 10%", 2040330 },
	{ "Scroll for Earring for LUK 10%", 2040331 },
	{ "Scroll for Earring for INT 50%", 2040333 },
	{ "Scroll for Earring for INT 100%", 2040334 },
	{ "Scroll for Earring for DEX 65%", 2040335 },
	{ "Scroll for Earring for DEX 15%", 2040336 },
	{ "Scroll for Earring for LUK 65%", 2040337 },
	{ "Scroll for Earring for LUK 15%", 2040338 },
	{ "Scroll for Earring for HP 65%", 2040339 },
	{ "Scroll for Earring for HP 15%", 2040340 },
	{ "Scroll for Topwear for DEF", 2040400 },
	{ "Scroll for Topwear for DEF", 2040401 },
	{ "Scroll for Topwear for DEF", 2040402 },
	{ "Scroll for Topwear for DEF", 2040403 },
	{ "Dark scroll for Topwear for DEF", 2040404 },
	{ "Dark scroll for Topwear for DEF", 2040405 },
	{ "Dark scroll for Topwear for STR", 2040406 },
	{ "Dark scroll for Topwear for STR", 2040407 },
	{ "Dark scroll for Topwear for HP", 2040408 },
	{ "Dark scroll for Topwear for HP", 2040409 },
	{ "Dark Scroll for Topwear for LUK", 2040410 },
	{ "Dark Scroll for Topwear for LUK", 2040411 },
	{ "Scroll for Topwear for LUK", 2040412 },
	{ "Scroll for Topwear for LUK", 2040413 },
	{ "Scroll for Topwear for LUK", 2040414 },
	{ "Scroll for Topwear for DEF", 2040415 },
	{ "Scroll for Topwear for DEF", 2040416 },
	{ "Scroll for Topwear for STR 100%", 2040417 },
	{ "Scroll for Topwear for STR 60%", 2040418 },
	{ "Scroll for Topwear for STR 10%", 2040419 },
	{ "Scroll for Topwear for HP 100%", 2040420 },
	{ "Scroll for Topwear for HP 60%", 2040421 },
	{ "Scroll for Topwear for HP 10%", 2040422 },
	{ "Scroll for Topwear for LUK 100%", 2040423 },
	{ "Scroll for Topwear for LUK 70%", 2040424 },
	{ "Scroll for Topwear for LUK 60%", 2040425 },
	{ "Scroll for Topwear for LUK 30%", 2040426 },
	{ "Scroll for Topwear for LUK 10%", 2040427 },
	{ "Scroll for Topwear for DEF 50%", 2040429 },
	{ "Scroll for Topwear for DEF 100%", 2040430 },
	{ "Scroll for Topwear for STR 65%", 2040431 },
	{ "Scroll for Topwear for STR 15%", 2040432 },
	{ "Scroll for Topwear for HP 65%", 2040433 },
	{ "Scroll for Topwear for HP 15%", 2040434 },
	{ "Scroll for Topwear for LUK 65%", 2040435 },
	{ "Scroll for Topwear for LUK 15%", 2040436 },
	{ "Scroll for Overall Armor for DEX", 2040500 },
	{ "Scroll for Overall Armor for DEX", 2040501 },
	{ "Scroll for Overall Armor for DEX", 2040502 },
	{ "Scroll for Overall Armor for DEF", 2040503 },
	{ "Scroll for Overall Armor for DEF", 2040504 },
	{ "Scroll for Overall Armor for DEF", 2040505 },
	{ "Scroll for Overall Armor for DEX", 2040506 },
	{ "Scroll for Overall Armor for DEF", 2040507 },
	{ "Dark scroll for Overall Armor for DEX", 2040508 },
	{ "Dark scroll for Overall Armor for DEX", 2040509 },
	{ "Dark scroll for Overall Armor for DEF", 2040510 },
	{ "Dark scroll for Overall Armor for DEF", 2040511 },
	{ "Scroll for Overall Armor for INT", 2040512 },
	{ "Scroll for Overall Armor for INT", 2040513 },
	{ "Scroll for Overall Armor for INT", 2040514 },
	{ "Scroll for Overall Armor for LUK", 2040515 },
	{ "Scroll for Overall Armor for LUK", 2040516 },
	{ "Scroll for Overall Armor for LUK", 2040517 },
	{ "Dark scroll for Overall Armor for INT", 2040518 },
	{ "Dark scroll for Overall Armor for INT", 2040519 },
	{ "Dark scroll for Overall Armor for LUK", 2040520 },
	{ "Dark scroll for Overall Armor for LUK", 2040521 },
	{ "Scroll for Overall Armor for DEX", 2040522 },
	{ "Scroll for Overall Armor for DEX", 2040523 },
	{ "Overall Armor Scroll for DEF", 2040524 },
	{ "Overall Armor Scroll for DEF", 2040525 },
	{ "Scroll for Overall Armor for INT", 2040526 },
	{ "Scroll for Overall Armor for INT", 2040527 },
	{ "Scroll for Overall Armor for LUK", 2040528 },
	{ "Scroll for Overall Armor for LUK", 2040529 },
	{ "Scroll for Overall for STR 100%", 2040530 },
	{ "Scroll for Overall for STR 70%", 2040531 },
	{ "Scroll for Overall for STR 60%", 2040532 },
	{ "Scroll for Overall for STR 30%", 2040533 },
	{ "Scroll for Overall for STR 10%", 2040534 },
	{ "Scroll for Overall Armor for DEX 100%", 2040538 },
	{ "Scroll for Overall Armor for DEF 100%", 2040539 },
	{ "Scroll for Overall Armor for STR 65%", 2040540 },
	{ "Scroll for Overall Armor for STR 15%", 2040541 },
	{ "Scroll for Overall Armor for DEX 50%", 2040542 },
	{ "Scroll for Overall Armor for DEF 50%", 2040543 },
	{ "Scroll for Bottomwear for DEF", 2040600 },
	{ "Scroll for Bottomwear for DEF", 2040601 },
	{ "Scroll for Bottomwear for DEF", 2040602 },
	{ "Scroll for Bottomwear for DEF", 2040603 },
	{ "Dark scroll for Bottomwear for DEF", 2040604 },
	{ "Dark scroll for Bottomwear for DEF", 2040605 },
	{ "Dark scroll for Bottomwear for Jump", 2040606 },
	{ "Dark scroll for Bottomwear for Jump", 2040607 },
	{ "Dark scroll for Bottomwear for HP", 2040608 },
	{ "Dark scroll for Bottomwear for HP", 2040609 },
	{ "Dark Scroll for Bottomwear for DEX", 2040610 },
	{ "Dark Scroll for Bottomwear for DEX", 2040611 },
	{ "Scroll for Bottomwear for DEX", 2040612 },
	{ "Scroll for Bottomwear for DEX", 2040613 },
	{ "Scroll for Bottomwear for DEX", 2040614 },
	{ "Scroll for Bottomwear for DEF", 2040615 },
	{ "Scroll for Bottomwear for DEF", 2040616 },
	{ "Scroll for Bottomwear for Jump 100%", 2040617 },
	{ "Scroll for Bottomwear for Jump 60%", 2040618 },
	{ "Scroll for Bottomwear for Jump 10%", 2040619 },
	{ "Scroll for Bottomwear for HP 100%", 2040620 },
	{ "Scroll for Bottomwear for HP 60%", 2040621 },
	{ "Scroll for Bottomwear for HP 10%", 2040622 },
	{ "Scroll for Bottomwear for DEX 100%", 2040623 },
	{ "Scroll for Bottomwear for DEX 70%", 2040624 },
	{ "Scroll for Bottomwear for DEX 60%", 2040625 },
	{ "Scroll for Bottomwear for DEX 30%", 2040626 },
	{ "Scroll for Bottomwear for DEX 10%", 2040627 },
	{ "Scroll for Bottomwear for DEF 50%", 2040629 },
	{ "Scroll for Bottomwear for DEF 100%", 2040630 },
	{ "Scroll for Bottomwear for Jump 65%", 2040631 },
	{ "Scroll for Bottomwear for Jump 15%", 2040632 },
	{ "Scroll for Bottomwear for HP 65%", 2040633 },
	{ "Scroll for Bottomwear for HP 15%", 2040634 },
	{ "Scroll for Bottomwear for DEX 65%", 2040635 },
	{ "Scroll for Bottomwear for DEX 15%", 2040636 },
	{ "Scroll for Shoes for DEX", 2040700 },
	{ "Scroll for Shoes for DEX", 2040701 },
	{ "Scroll for Shoes for DEX", 2040702 },
	{ "Scroll for Shoes for Jump", 2040703 },
	{ "Scroll for Shoes for Jump", 2040704 },
	{ "Scroll for Shoes for Jump", 2040705 },
	{ "Scroll for Shoes for Speed", 2040706 },
	{ "Scroll for Shoes for Speed", 2040707 },
	{ "Scroll for Shoes for Speed", 2040708 },
	{ "Scroll for Shoes for DEX", 2040709 },
	{ "Scroll for Shoes for Jump", 2040710 },
	{ "Scroll for Shoes for Speed", 2040711 },
	{ "Dark scroll for Shoes for DEX", 2040712 },
	{ "Dark scroll for Shoes for DEX", 2040713 },
	{ "Dark scroll for Shoes for Jump", 2040714 },
	{ "Dark scroll for Shoes for Jump", 2040715 },
	{ "Dark scroll for Shoes for Speed", 2040716 },
	{ "Dark scroll for Shoes for Speed", 2040717 },
	{ "Scroll for Shoes for DEX", 2040718 },
	{ "Scroll for Shoes for DEX", 2040719 },
	{ "Scroll for Jump for DEX", 2040720 },
	{ "Scroll for Jump for DEX", 2040721 },
	{ "Scroll for Speed for DEX", 2040722 },
	{ "Scroll for Speed for DEX", 2040723 },
	{ "Scroll for Spikes on Shoes 10%", 2040727 },
	{ "Balrog's STR Scroll 30%", 2040728 },
	{ "Balrog's INT Scroll 30%", 2040729 },
	{ "Balrog's LUK Scroll 30%", 2040730 },
	{ "Balrog's DEX Scroll 30%", 2040731 },
	{ "Balrog's HP Scroll 30%", 2040732 },
	{ "Balrog's MP Scroll 30%", 2040733 },
	{ "Balrog's Speed Scroll 30%", 2040734 },
	{ "Balrog's Jump Scroll 30%", 2040735 },
	{ "Balrog's Accuracy Scroll 30%", 2040736 },
	{ "Balrog's Avoidability Scroll 30%", 2040737 },
	{ "Balrog's Defense Scroll 30%", 2040738 },
	{ "Balrog's Twilight Scroll 5%", 2040739 },
	{ "Scroll for Shoes for DEX 100%", 2040740 },
	{ "Scroll for Shoes for Jump 100%", 2040741 },
	{ "Scroll for Shoes for Speed 100%", 2040742 },
	{ "Scroll for Shoes for DEX 50%", 2040755 },
	{ "Scroll for Shoes for Jump 50%", 2040756 },
	{ "Scroll for Shoes for Speed 50%", 2040757 },
	{ "Scroll for Shoes for ATT", 2040758 },
	{ "Scroll for Shoes for ATT", 2040759 },
	{ "Scroll for Shoes for ATT", 2040760 },
	{ "Scroll for Gloves for DEX", 2040800 },
	{ "Scroll for Gloves for DEX", 2040801 },
	{ "Scroll for Gloves for DEX", 2040802 },
	{ "Scroll for Gloves for ATT", 2040803 },
	{ "Scroll for Gloves for ATT", 2040804 },
	{ "Scroll for Gloves for ATT", 2040805 },
	{ "Scroll for Gloves for DEX", 2040806 },
	{ "Scroll for Gloves for ATT", 2040807 },
	{ "Dark scroll for Gloves for DEX", 2040808 },
	{ "Dark scroll for Gloves for DEX", 2040809 },
	{ "Dark scroll for Gloves for ATT", 2040810 },
	{ "Dark scroll for Gloves for ATT", 2040811 },
	{ "Dark scroll for Gloves for HP", 2040812 },
	{ "Dark scroll for Gloves for HP", 2040813 },
	{ "Dark Scroll for Gloves for Magic Att.", 2040814 },
	{ "Dark Scroll for Gloves for Magic Att.", 2040815 },
	{ "Scroll for Gloves for Magic Att.", 2040816 },
	{ "Scroll for Gloves for Magic Att.", 2040817 },
	{ "Scroll for Gloves for Magic Att.", 2040818 },
	{ "Scroll for Gloves for DEX", 2040819 },
	{ "Scroll for Gloves for DEX", 2040820 },
	{ "Scroll for Gloves for ATT", 2040821 },
	{ "Scroll for Gloves for ATT", 2040822 },
	{ "Scroll for Gloves for HP 100%", 2040823 },
	{ "Scroll for Gloves for HP 60%", 2040824 },
	{ "Scroll for Gloves for HP 10%", 2040825 },
	{ "Scroll for Gloves for ATT 60%", 2040826 },
	{ "Scroll for Gloves for DEX 100%", 2040829 },
	{ "Scroll for Gloves for ATT 100%", 2040830 },
	{ "Scroll for Gloves for HP 65%", 2040831 },
	{ "Scroll for Gloves for HP 15%", 2040832 },
	{ "Scroll for Gloves for DEX 50%", 2040833 },
	{ "Scroll for Gloves for ATT 50%", 2040834 },
	{ "Scroll for Shield for DEF", 2040900 },
	{ "Scroll for Shield for DEF", 2040901 },
	{ "Scroll for Shield for DEF", 2040902 },
	{ "Scroll for Shield for DEF", 2040903 },
	{ "Dark scroll for Shield for DEF", 2040904 },
	{ "Dark scroll for Shield for DEF", 2040905 },
	{ "Dark scroll for Shield for LUK", 2040906 },
	{ "Dark scroll for Shield for LUK", 2040907 },
	{ "Dark scroll for Shield for HP", 2040908 },
	{ "Dark scroll for Shield for HP", 2040909 },
	{ "Scroll for Shield for DEF", 2040910 },
	{ "Scroll for Shield for DEF", 2040911 },
	{ "[4yrAnniv]Scroll for Shield for DEF", 2040912 },
	{ "Scroll for Shield for Weapon Att.", 2040914 },
	{ "Scroll for Shield for Weapon Att.", 2040915 },
	{ "Dark Scroll for Shield for Weapon Att.", 2040916 },
	{ "Dark Scroll for Shield for Weapon Att.", 2040917 },
	{ "Scroll for Shield for Magic Att.", 2040918 },
	{ "Scroll for Shield for Magic Att.", 2040919 },
	{ "Scroll for Shield for Magic Att.", 2040920 },
	{ "Dark Scroll for Shield for Magic Att.", 2040921 },
	{ "Dark Scroll for Shield for Magic Att.", 2040922 },
	{ "Scroll for Shield for LUK 100%", 2040923 },
	{ "Scroll for Shield for LUK 60%", 2040924 },
	{ "Scroll for Shield for LUK 10%", 2040925 },
	{ "Scroll for Shield for HP 100%", 2040926 },
	{ "Scroll for Shield for HP 60%", 2040927 },
	{ "Scroll for Shield for HP 10%", 2040928 },
	{ "Scroll for Shield for STR 100%", 2040929 },
	{ "Scroll for Shield for STR 70%", 2040930 },
	{ "Scroll for Shield for STR 60%", 2040931 },
	{ "Scroll for Shield for STR 30%", 2040932 },
	{ "Scroll for Shield for STR 10%", 2040933 },
	{ "Scroll for Shield for DEF 100%", 2040936 },
	{ "Scroll for Shield for LUK 65%", 2040937 },
	{ "Scroll for Shield for LUK 15%", 2040938 },
	{ "Scroll for Shield for HP 65%", 2040939 },
	{ "Scroll for Shield for HP 15%", 2040940 },
	{ "Scroll for Shield for STR 65%", 2040941 },
	{ "Scroll for Shield for STR 15%", 2040942 },
	{ "Scroll for Shield for DEF 50%", 2040943 },
	{ "Scroll for Cape for Magic Def.", 2041000 },
	{ "Scroll for Cape for Magic Def.", 2041001 },
	{ "Scroll for Cape for Magic Def.", 2041002 },
	{ "Scroll for Cape for Weapon Def.", 2041003 },
	{ "Scroll for Cape for Weapon Def.", 2041004 },
	{ "Scroll for Cape for Weapon Def.", 2041005 },
	{ "Scroll for Cape for HP", 2041006 },
	{ "Scroll for Cape for HP", 2041007 },
	{ "Scroll for Cape for HP", 2041008 },
	{ "Scroll for Cape for MP", 2041009 },
	{ "Scroll for Cape for MP", 2041010 },
	{ "Scroll for Cape for MP", 2041011 },
	{ "Scroll for Cape for STR", 2041012 },
	{ "Scroll for Cape for STR", 2041013 },
	{ "Scroll for Cape for STR", 2041014 },
	{ "Scroll for Cape for INT", 2041015 },
	{ "Scroll for Cape for INT", 2041016 },
	{ "Scroll for Cape for INT", 2041017 },
	{ "Scroll for Cape for DEX", 2041018 },
	{ "Scroll for Cape for DEX", 2041019 },
	{ "Scroll for Cape for DEX", 2041020 },
	{ "Scroll for Cape for LUK", 2041021 },
	{ "Scroll for Cape for LUK", 2041022 },
	{ "Scroll for Cape for LUK", 2041023 },
	{ "Scroll for Cape for Magic Def.", 2041024 },
	{ "Scroll for Cape for Weapon Def.", 2041025 },
	{ "Dark scroll for Cape for Magic Def.", 2041026 },
	{ "Dark scroll for Cape for Magic Def.", 2041027 },
	{ "Dark scroll for Cape for Weapon Def.", 2041028 },
	{ "Dark scroll for Cape for Weapon Def.", 2041029 },
	{ "Dark scroll for Cape for HP", 2041030 },
	{ "Dark scroll for Cape for HP", 2041031 },
	{ "Dark scroll for Cape for MP", 2041032 },
	{ "Dark scroll for Cape for MP", 2041033 },
	{ "Dark scroll for Cape for STR", 2041034 },
	{ "Dark scroll for Cape for STR", 2041035 },
	{ "Dark scroll for Cape for INT", 2041036 },
	{ "Dark scroll for Cape for INT", 2041037 },
	{ "Dark scroll for Cape for DEX", 2041038 },
	{ "Dark scroll for Cape for DEX", 2041039 },
	{ "Dark scroll for Cape for LUK", 2041040 },
	{ "Dark scroll for Cape for LUK", 2041041 },
	{ "Scroll for Cape for Magic DEF", 2041042 },
	{ "Scroll for Cape for Magic DEF", 2041043 },
	{ "Scroll for Cape for Weapon DEF", 2041044 },
	{ "Scroll for Cape for Weapon DEF", 2041045 },
	{ "Scroll for Cape for MaxHP", 2041046 },
	{ "Scroll for Cape for MaxHP", 2041047 },
	{ "Scroll for Cape for MP", 2041048 },
	{ "Scroll for Cape for MP", 2041049 },
	{ "Scroll for Cape for STR", 2041050 },
	{ "Scroll for Cape for STR", 2041051 },
	{ "Scroll for Cape for INT", 2041052 },
	{ "Scroll for Cape for INT", 2041053 },
	{ "Scroll for Cape for DEX", 2041054 },
	{ "Scroll for Cape for DEX", 2041055 },
	{ "Scroll for Cape for LUK", 2041056 },
	{ "Scroll for Cape for LUK", 2041057 },
	{ "Scroll for Cape for Cold Protection 10%", 2041058 },
	{ "[4yrAnniv] Scroll for Cape for STR 20%", 2041059 },
	{ "[4yrAnniv] Scroll for Cape for INT 20%", 2041060 },
	{ "[4yrAnniv] Scroll for Cape for DEX 20%", 2041061 },
	{ "[4yrAnniv] Scroll for Cape for LUK 20%", 2041062 },
	{ "Scroll for Cape for Magic DEF 100%", 2041066 },
	{ "Scroll for Cape for Weapon DEF 100%", 2041067 },
	{ "Scroll for Cape for Magic Def. 50%", 2041068 },
	{ "Scroll for Cape for Weapon Def. 50%", 2041069 },
	{ "Scroll for Ring for STR 100%", 2041100 },
	{ "Scroll for Rings for STR 60%", 2041101 },
	{ "Scroll for Rings for STR 10%", 2041102 },
	{ "Scroll for Rings for INT 100%", 2041103 },
	{ "Scroll for Rings for INT 60%", 2041104 },
	{ "Scroll for Rings for INT 10%", 2041105 },
	{ "Scroll for Rings for DEX 100%", 2041106 },
	{ "Scroll for Rings for DEX 60%", 2041107 },
	{ "Scroll for Rings for DEX 10%", 2041108 },
	{ "Scroll for Rings for LUK 100%", 2041109 },
	{ "Scroll for Rings for LUK 60%", 2041110 },
	{ "Scroll for Rings for LUK 10%", 2041111 },
	{ "Dark Scroll for Rings for STR 70%", 2041112 },
	{ "Dark Scroll for Rings for STR 30%", 2041113 },
	{ "Dark Scroll for Rings for INT 70%", 2041114 },
	{ "Dark Scroll for Rings for INT 30%", 2041115 },
	{ "Dark Scroll for Rings for DEX 70%", 2041116 },
	{ "Dark Scroll for Rings for DEX 30%", 2041117 },
	{ "Dark Scroll for Rings for LUK 70%", 2041118 },
	{ "Dark Scroll for Rings for LUK 30%", 2041119 },
	{ "Dragon Stone", 2041200 },
	{ "Spiegelmann's Marble", 2041211 },
	{ "Rock of Wisdom", 2041212 },
	{ "Scroll for Belts for STR 100%", 2041300 },
	{ "Scroll for Belts for STR 60%", 2041301 },
	{ "Scroll for Belts for STR 10%", 2041302 },
	{ "Scroll for Belts for INT 100%", 2041303 },
	{ "Scroll for Belts for INT 60%", 2041304 },
	{ "Scroll for Belts for INT 10%", 2041305 },
	{ "Scroll for Belts for DEX 100%", 2041306 },
	{ "Scroll for Belts for DEX 60%", 2041307 },
	{ "Scroll for Belts for DEX 10%", 2041308 },
	{ "Scroll for Belts for LUK 100%", 2041309 },
	{ "Scroll for Belts for LUK 60%", 2041310 },
	{ "Scroll for Belts for LUK 10%", 2041311 },
	{ "Dark Scroll for Belts for STR 70%", 2041312 },
	{ "Dark Scroll for Belts for STR 30%", 2041313 },
	{ "Dark Scroll for Belts for INT 70%", 2041314 },
	{ "Dark Scroll for Belts for INT 30%", 2041315 },
	{ "Dark Scroll for Belts for DEX 70%", 2041316 },
	{ "Dark Scroll for Belts for DEX 30%", 2041317 },
	{ "Dark Scroll for Belts for LUK 70%", 2041318 },
	{ "Dark Scroll for Belts for LUK 30%", 2041319 },
	{ "Scroll for One-Handed Sword for ATT", 2043000 },
	{ "Scroll for One-Handed Sword for ATT", 2043001 },
	{ "Scroll for One-Handed Sword for ATT", 2043002 },
	{ "Scroll for One-Handed Sword for ATT", 2043003 },
	{ "Dark scroll for One-Handed Sword for ATT", 2043004 },
	{ "Dark scroll for One-Handed Sword for ATT", 2043005 },
	{ "Dark Scroll for One-Handed Sword for Magic Att.", 2043006 },
	{ "Dark Scroll for One-Handed Sword for Magic Att.", 2043007 },
	{ "Scroll for One-Handed Sword for Magic Att.", 2043008 },
	{ "Scroll for One-Handed Sword for Magic Att.", 2043009 },
	{ "Scroll for One-Handed Sword for Magic Att.", 2043010 },
	{ "Scroll for One-Handed Sword for ATT", 2043011 },
	{ "Scroll for One-Handed Sword for ATT", 2043012 },
	{ "[4yrAnniv]Scroll for One-Handed Sword for ATT", 2043013 },
	{ "Scroll for One-Handed Sword for Accuracy 100%", 2043015 },
	{ "Scroll for One-Handed Sword for Accuracy 70%", 2043016 },
	{ "Scroll for One-Handed Sword for Accuracy 60%", 2043017 },
	{ "Scroll for One-Handed Sword for Accuracy 30%", 2043018 },
	{ "Scroll for One-Handed Sword for Accuracy 10%", 2043019 },
	{ "King Pepe's 60% Scroll for One-handed Sword Attacks", 2043021 },
	{ "Scroll for One-Handed Sword for ATT 50%", 2043022 },
	{ "Scroll for One-Handed Sword for ATT 100%", 2043023 },
	{ "Scroll for One-Handed Sword for Accuracy 65%", 2043024 },
	{ "Scroll for One-Handed Sword for Accuracy 15%", 2043025 },
	{ "Scroll for One-Handed Axe for ATT", 2043100 },
	{ "Scroll for One-Handed Axe for ATT", 2043101 },
	{ "Scroll for One-Handed Axe for ATT", 2043102 },
	{ "Scroll for One-Handed Axe for ATT", 2043103 },
	{ "Dark scroll for One-Handed Axe for ATT", 2043104 },
	{ "Dark scroll for One-Handed Axe for ATT", 2043105 },
	{ "Scroll for One-Handed Axe for ATT", 2043106 },
	{ "Scroll for One-Handed Axe for ATT", 2043107 },
	{ "[4yrAnniv]Scroll for One-Handed Axe for ATT", 2043108 },
	{ "Scroll for One-Handed Axe for Accuracy 100%", 2043110 },
	{ "Scroll for One-Handed Axe for Accuracy 70%", 2043111 },
	{ "Scroll for One-Handed Axe for Accuracy 60%", 2043112 },
	{ "Scroll for One-Handed Axe for Accuracy 30%", 2043113 },
	{ "Scroll for One-Handed Axe for Accuracy 10%", 2043114 },
	{ "King Pepe's 60% Scroll for One-handed Axe Attacks", 2043116 },
	{ "Scroll for One-Handed Axe for ATT 100%", 2043117 },
	{ "Scroll for One-Handed Axe for Accuracy 65%", 2043118 },
	{ "Scroll for One-Handed Axe for Accuracy 15%", 2043119 },
	{ "Scroll for One-Handed Axe for ATT 50%", 2043120 },
	{ "Scroll for One-Handed BW for ATT", 2043200 },
	{ "Scroll for One-Handed BW for ATT", 2043201 },
	{ "Scroll for One-Handed BW for ATT", 2043202 },
	{ "Scroll for One-Handed BW for ATT", 2043203 },
	{ "Dark scroll for One-Handed BW for ATT", 2043204 },
	{ "Dark scroll for One-Handed BW for ATT", 2043205 },
	{ "Scroll for One-Handed BW for ATT", 2043206 },
	{ "Scroll for One-Handed BW for ATT", 2043207 },
	{ "[4yrAnniv]Scroll for One-Handed BW for ATT", 2043208 },
	{ "Scroll for One-Handed BW for Accuracy 100%", 2043210 },
	{ "Scroll for One-Handed BW for Accuracy 70%", 2043211 },
	{ "Scroll for One-Handed BW for Accuracy 60%", 2043212 },
	{ "Scroll for One-Handed BW for Accuracy 30%", 2043213 },
	{ "Scroll for One-Handed BW for Accuracy 10%", 2043214 },
	{ "King Pepe's 60% Scroll for One-handed BW Attacks", 2043216 },
	{ "Scroll for One-Handed BW for ATT 100%", 2043217 },
	{ "Scroll for One-Handed BW for Accuracy 65%", 2043218 },
	{ "Scroll for One-Handed BW for Accuracy 15%", 2043219 },
	{ "Scroll for One-Handed BW for ATT 50%", 2043220 },
	{ "Scroll for Dagger for ATT", 2043300 },
	{ "Scroll for Dagger for ATT", 2043301 },
	{ "Scroll for Dagger for ATT", 2043302 },
	{ "Scroll for Dagger for ATT", 2043303 },
	{ "Dark scroll for Dagger for ATT", 2043304 },
	{ "Dark scroll for Dagger for ATT", 2043305 },
	{ "Scroll for Dagger for ATT", 2043306 },
	{ "Scroll for Dagger for ATT", 2043307 },
	{ "[4yrAnniv]Scroll for Dagger for ATT", 2043308 },
	{ "King Pepe's 60% Scroll for Dagger Attacks", 2043311 },
	{ "Scroll for Dagger for ATT 100%", 2043312 },
	{ "Scroll for Dagger for ATT 50%", 2043313 },
	{ "Scroll for Wand for Magic Att.", 2043700 },
	{ "Scroll for Wand for Magic Att.", 2043701 },
	{ "Scroll for Wand for Magic Att.", 2043702 },
	{ "Scroll for Wand for Magic Att.", 2043703 },
	{ "Dark scroll for Wand for Magic Att.", 2043704 },
	{ "Dark scroll for Wand for Magic Att.", 2043705 },
	{ "Scroll for Wand for Magic Att.", 2043706 },
	{ "Scroll for Wand for Magic Att.", 2043707 },
	{ "[4yrAnniv]Scroll for Wand for Magic Att.", 2043708 },
	{ "King Pepe's 60% Scroll for Wand Magic Attacks", 2043711 },
	{ "Scroll for Wand for Magic ATT 100%", 2043712 },
	{ "Scroll for Wand for Magic Att. 50%", 2043713 },
	{ "Scroll for Staff for Magic Att.", 2043800 },
	{ "Scroll for Staff for Magic Att.", 2043801 },
	{ "Scroll for Staff for Magic Att.", 2043802 },
	{ "Scroll for Staff for Magic Att.", 2043803 },
	{ "Dark scroll for Staff for Magic Att.", 2043804 },
	{ "Dark scroll for Staff for Magic Att.", 2043805 },
	{ "Scroll for Staff for Magic Att.", 2043806 },
	{ "Scroll for Staff for Magic Att.", 2043807 },
	{ "[4yrAnniv]Scroll for Staff for Magic Att.", 2043808 },
	{ "King Pepe's 60% Scroll for Staff Magic Attacks", 2043811 },
	{ "Scroll for Staff for Magic ATT 100%", 2043812 },
	{ "Scroll for Staff for Magic Att. 50%", 2043813 },
	{ "Scroll for Two-handed Sword for ATT", 2044000 },
	{ "Scroll for Two-handed Sword for ATT", 2044001 },
	{ "Scroll for Two-handed Sword for ATT", 2044002 },
	{ "Scroll for Two-handed Sword for ATT", 2044003 },
	{ "Dark scroll for Two-handed Sword for ATT", 2044004 },
	{ "Dark scroll for Two-handed Sword for ATT", 2044005 },
	{ "Scroll for Two-Handed Sword for ATT", 2044006 },
	{ "Scroll for Two-Handed Sword for ATT", 2044007 },
	{ "[4yrAnniv]Scroll for Two-Handed Sword for ATT", 2044008 },
	{ "Scroll for Two-Handed Sword for Accuracy 100%", 2044010 },
	{ "Scroll for Two-Handed Sword for Accuracy 70%", 2044011 },
	{ "Scroll for Two-Handed Sword for Accuracy 60%", 2044012 },
	{ "Scroll for Two-Handed Sword for Accuracy 30%", 2044013 },
	{ "Scroll for Two-Handed Sword for Accuracy 10%", 2044014 },
	{ "Scroll for Two-Handed Swords for ATT 10%", 2044015 },
	{ "King Pepe's 60% Scroll for Two-handed Sword Attacks", 2044024 },
	{ "Scroll for Two-handed Sword for ATT 100%", 2044025 },
	{ "Scroll for Two-Handed Sword for Accuracy 65%", 2044026 },
	{ "Scroll for Two-Handed Sword for Accuracy 15%", 2044027 },
	{ "Scroll for Two-handed Sword for ATT 50%", 2044028 },
	{ "Scroll for Two-handed Axe for ATT", 2044100 },
	{ "Scroll for Two-handed Axe for ATT", 2044101 },
	{ "Scroll for Two-handed Axe for ATT", 2044102 },
	{ "Scroll for Two-handed Axe for ATT", 2044103 },
	{ "Dark scroll for Two-handed Axe for ATT", 2044104 },
	{ "Dark scroll for Two-handed Axe for ATT", 2044105 },
	{ "Scroll for Two-Handed Axe for ATT", 2044106 },
	{ "Scroll for Two-Handed Axe for ATT", 2044107 },
	{ "[4yrAnniv]Scroll for Two-Handed Axe for ATT", 2044108 },
	{ "Scroll for Two-Handed Axe for Accuracy 100%", 2044110 },
	{ "Scroll for Two-Handed Axe for Accuracy 70%", 2044111 },
	{ "Scroll for Two-Handed Axe for Accuracy 60%", 2044112 },
	{ "Scroll for Two-Handed Axe for Accuracy 30%", 2044113 },
	{ "Scroll for Two-Handed Axe for Accuracy 10%", 2044114 },
	{ "King Pepe's 60% Scroll for Two-handed Axe Attacks", 2044116 },
	{ "Scroll for Two-handed Axe for ATT 100%", 2044117 },
	{ "Scroll for Two-Handed Axe for Accuracy 65%", 2044118 },
	{ "Scroll for Two-Handed Axe for Accuracy 15%", 2044119 },
	{ "Scroll for Two-handed Axe for ATT 50%", 2044120 },
	{ "Scroll for Two-handed BW for ATT", 2044200 },
	{ "Scroll for Two-handed BW for ATT", 2044201 },
	{ "Scroll for Two-handed BW for ATT", 2044202 },
	{ "Scroll for Two-handed BW for ATT", 2044203 },
	{ "Dark scroll for Two-handed BW for ATT", 2044204 },
	{ "Dark scroll for Two-handed BW for ATT", 2044205 },
	{ "Scroll for Two-Handed BW for ATT", 2044206 },
	{ "Scroll for Two-Handed BW for ATT", 2044207 },
	{ "[4yrAnniv]Scroll for Two-Handed BW for ATT", 2044208 },
	{ "Scroll for Two-Handed BW for Accuracy 100%", 2044210 },
	{ "Scroll for Two-Handed BW for Accuracy 70%", 2044211 },
	{ "Scroll for Two-Handed BW for Accuracy 60%", 2044212 },
	{ "Scroll for Two-Handed BW for Accuracy 30%", 2044213 },
	{ "Scroll for Two-Handed BW for Accuracy 10%", 2044214 },
	{ "King Pepe's 60% Scroll for Two-handed BW Attacks", 2044216 },
	{ "Scroll for Two-handed BW for ATT 100%", 2044217 },
	{ "Scroll for Two-Handed BW for Accuracy 65%", 2044218 },
	{ "Scroll for Two-Handed BW for Accuracy 15%", 2044219 },
	{ "Scroll for Two-handed BW for ATT 50%", 2044220 },
	{ "Scroll for Spear for ATT", 2044300 },
	{ "Scroll for Spear for ATT", 2044301 },
	{ "Scroll for Spear for ATT", 2044302 },
	{ "Scroll for Spear for ATT", 2044303 },
	{ "Dark scroll for Spear for ATT", 2044304 },
	{ "Dark scroll for Spear for ATT", 2044305 },
	{ "Scroll for Spear for ATT", 2044306 },
	{ "Scroll for Spear for ATT", 2044307 },
	{ "[4yrAnniv]Scroll for Spear for ATT", 2044308 },
	{ "Scroll for Spear for Accuracy 100%", 2044310 },
	{ "Scroll for Spear for Accuracy 70%", 2044311 },
	{ "Scroll for Spear for Accuracy 60%", 2044312 },
	{ "Scroll for Spear for Accuracy 30%", 2044313 },
	{ "Scroll for Spear for Accuracy 10%", 2044314 },
	{ "King Pepe's 60% Scroll for Spear Attacks", 2044316 },
	{ "Scroll for Spear for ATT 100%", 2044317 },
	{ "Scroll for Spears for Accuracy 65%", 2044318 },
	{ "Scroll for Spears for Accuracy 15%", 2044319 },
	{ "Scroll for Spear for ATT 50%", 2044320 },
	{ "Scroll for Pole Arm for ATT", 2044400 },
	{ "Scroll for Pole Arm for ATT", 2044401 },
	{ "Scroll for Pole Arm for ATT", 2044402 },
	{ "Scroll for Pole Arm for ATT", 2044403 },
	{ "Dark scroll for Pole Arm for ATT", 2044404 },
	{ "Dark scroll for Pole Arm for ATT", 2044405 },
	{ "Scroll for Pole Arm for ATT", 2044406 },
	{ "Scroll for Pole Arm for ATT", 2044407 },
	{ "[4yrAnniv]Scroll for Pole Arm for ATT", 2044408 },
	{ "Scroll for Pole-Arm for Accuracy 100%", 2044410 },
	{ "Scroll for Pole-Arm for Accuracy 70%", 2044411 },
	{ "Scroll for Pole-Arm for Accuracy 60%", 2044412 },
	{ "Scroll for Pole-Arm for Accuracy 30%", 2044413 },
	{ "Scroll for Pole-Arm for Accuracy 10%", 2044414 },
	{ "King Pepe's 60% Scroll for Polearm Attacks", 2044416 },
	{ "Scroll for Pole Arm for ATT 100%", 2044417 },
	{ "Scroll for Polearm for Accuracy 65%", 2044418 },
	{ "Scroll for Polearm for Accuracy 15%", 2044419 },
	{ "Scroll for Pole Arm for ATT 50%", 2044420 },
	{ "Scroll for Bow for ATT", 2044500 },
	{ "Scroll for Bow for ATT", 2044501 },
	{ "Scroll for Bow for ATT", 2044502 },
	{ "Scroll for Bow for ATT", 2044503 },
	{ "Dark scroll for Bow for ATT", 2044504 },
	{ "Dark scroll for Bow for ATT", 2044505 },
	{ "Scroll for Bow for ATT", 2044506 },
	{ "Scroll for Bow for ATT", 2044507 },
	{ "[4yrAnniv]Scroll for Bow for ATT", 2044508 },
	{ "King Pepe's 60% Scroll for Bow Attacks", 2044511 },
	{ "Scroll for Bow for ATT 100%", 2044512 },
	{ "Scroll for Bow for ATT 50%", 2044513 },
	{ "Scroll for Crossbow for ATT", 2044600 },
	{ "Scroll for Crossbow for ATT", 2044601 },
	{ "Scroll for Crossbow for ATT", 2044602 },
	{ "Scroll for Crossbow for ATT", 2044603 },
	{ "Dark scroll for Crossbow for ATT", 2044604 },
	{ "Dark scroll for Crossbow for ATT", 2044605 },
	{ "Scroll for Crossbow for ATT", 2044606 },
	{ "Scroll for Crossbow for ATT", 2044607 },
	{ "[4yrAnniv]Scroll for Crossbow for ATT", 2044608 },
	{ "King Pepe's 60% Scroll for Crossbow Attacks", 2044611 },
	{ "Scroll for Crossbow for ATT 100%", 2044612 },
	{ "Scroll for Crossbow for ATT 50%", 2044613 },
	{ "Scroll for Claw for ATT", 2044700 },
	{ "Scroll for Claw for ATT", 2044701 },
	{ "Scroll for Claw for ATT", 2044702 },
	{ "Scroll for Claw for ATT", 2044703 },
	{ "Dark Scroll for Claw for ATT", 2044704 },
	{ "Dark scroll for Claw for ATT", 2044705 },
	{ "Scroll for Claw for ATT", 2044706 },
	{ "Scroll for Claw for ATT", 2044707 },
	{ "[4yrAnniv]Scroll for Claw for ATT", 2044708 },
	{ "King Pepe's 60% Scroll for Thief Attacks", 2044711 },
	{ "Scroll for Claw for ATT 100%", 2044712 },
	{ "Scroll for Claw for ATT 50%", 2044713 },
	{ "Scroll for Knuckler for Attack 100%", 2044800 },
	{ "Scroll for Knuckler for Attack 60%", 2044801 },
	{ "Scroll for Knuckler for ATT", 2044802 },
	{ "Scroll for Knuckler for Attack 70%", 2044803 },
	{ "Scroll for Knuckler for Attack 30%", 2044804 },
	{ "Scroll for Knuckle for Accuracy 100%", 2044805 },
	{ "Scroll for Knuckle for Accuracy 70%", 2044806 },
	{ "Scroll for Knuckle for Accuracy 60%", 2044807 },
	{ "Scroll for Knuckle for Accuracy 30%", 2044808 },
	{ "Scroll for Knuckle for Accuracy 10%", 2044809 },
	{ "[4yrAnniv] Scroll for Knuckle for Attack 40%", 2044810 },
	{ "Scroll for Knuckles for ATT 65%", 2044811 },
	{ "Scroll for Knuckles for ATT 15%", 2044812 },
	{ "Scroll for Knuckles for Accuracy 65%", 2044813 },
	{ "Scroll for Knuckles for Accuracy 15%", 2044814 },
	{ "Scroll for Knuckler for Attack 100%", 2044815 },
	{ "King Pepe's 60% Scroll for Knuckle Attacks", 2044816 },
	{ "Scroll for Knuckler for Attack 50%", 2044817 },
	{ "Scroll for Gun for Attack 100%", 2044900 },
	{ "Scroll for Gun for Attack 60%", 2044901 },
	{ "Scroll for Gun for ATT", 2044902 },
	{ "Scroll for Gun for Attack 70%", 2044903 },
	{ "Scroll for Gun for Attack 30%", 2044904 },
	{ "[4yrAnniv] Gun for Attack 40%", 2044905 },
	{ "Gun ATT Scroll 65%", 2044906 },
	{ "Gun ATT Scroll 15%", 2044907 },
	{ "Scroll for Gun for Attack 100%", 2044908 },
	{ "King Pepe's 60% Scroll for Gun Attacks", 2044909 },
	{ "Scroll for Gun for Attack 50%", 2044910 },
	{ "Scroll for Pet Equip. for Speed", 2048000 },
	{ "Scroll for Pet Equip. for Speed", 2048001 },
	{ "Scroll for Pet Equip. for Speed", 2048002 },
	{ "Scroll for Pet Equip. for Jump", 2048003 },
	{ "Scroll for Pet Equip. for Jump", 2048004 },
	{ "Scroll for Pet Equip. for Jump", 2048005 },
	{ "Scroll for Speed for Pet Equip.", 2048006 },
	{ "Scroll for Speed for Pet Equip.", 2048007 },
	{ "Scroll for jump for Pet Equip.", 2048008 },
	{ "Scroll for jump for Pet Equip.", 2048009 },
	{ "Scroll for Pet Equip. for STR 60%", 2048010 },
	{ "Scroll for Pet Equip. for INT 60%", 2048011 },
	{ "Scroll for Pet Equip. for DEX 60%", 2048012 },
	{ "Scroll for Pet Equip. for LUK 60%", 2048013 },
	{ "Clean Slate Scroll 1%", 2049000 },
	{ "Clean Slate Scroll 3%", 2049001 },
	{ "Clean Slate Scroll 5%", 2049002 },
	{ "Clean Slate Scroll 20%", 2049003 },
	{ "Chaos Scroll 60%", 2049100 },
	{ "Liar Tree Sap 100%", 2049101 },
	{ "Maple Syrup 100%", 2049102 },
	{ "Beach Sandals Scroll 100%", 2049103 },
	{ "Agent Equipment Scroll 100%", 2049104 },
	{ "[6th Anniversary] Dark Scroll for Gloves for ATT 70%", 2049105 },
	{ "[6th Anniversary] Dark Scroll for Gloves for ATT 30%", 2049106 },
	{ "[6th Anniversary] Dark Scroll for Gloves for STR 70%   [", 2049107 },
	{ "[6th Anniversary] Dark Scroll for Gloves for LUK 70%", 2049108 },
	{ "[6th Anniversary] Dark Scroll for Gloves for INT 70%", 2049109 },
	{ "[6th Anniversary] Dark Scroll for Gloves for DEX 70%", 2049110 },
	{ "King Pepe's 100% Scroll for Weapons", 2049112 },
	{ "Normal Witch Scroll", 2049113 },
	{ "Witch's Belt Scroll", 2049114 },
	{ "Dark Scroll for Accessory for STR 70%  ", 2049200 },
	{ "Dark Scroll for Accessory for STR 30%", 2049201 },
	{ "Dark Scroll for Accessory for DEX 70%", 2049202 },
	{ "Dark Scroll for Accessory for DEX 30%", 2049203 },
	{ "Dark Scroll for Accessory for INT 70%", 2049204 },
	{ "Dark Scroll for Accessory for INT 30%", 2049205 },
	{ "Dark Scroll for Accessory for LUK 70%", 2049206 },
	{ "Dark Scroll for Accessory for LUK 30%", 2049207 },
	{ "Dark Scroll for Accessory for HP 70%", 2049208 },
	{ "Dark Scroll for Accessory for HP 30%", 2049209 },
	{ "Dark Scroll for Accessory for MP 70%", 2049210 },
	{ "Dark Scroll for Accessory for MP 30%", 2049211 },
	{ "Antidote", 2050000 },
	{ "Eyedrop", 2050001 },
	{ "Tonic", 2050002 },
	{ "Holy Water", 2050003 },
	{ "All Cure Potion", 2050004 },
	{ "One View", 2050005 },
	{ "Owl Potion", 2050006 },
	{ "The Lost eye", 2050098 },
	{ "Flaming feather", 2050099 },
	{ "Arrow for Bow", 2060000 },
	{ "Bronze Arrow for Bow", 2060001 },
	{ "Steel Arrow for Bow", 2060002 },
	{ "Red Arrow for Bow", 2060003 },
	{ "Diamond Arrow for Bow", 2060004 },
	{ "Snowball", 2060005 },
	{ "Big Snowball", 2060006 },
	{ "Arrow for Crossbow", 2061000 },
	{ "Bronze Arrow for Crossbow", 2061001 },
	{ "Steel Arrow for Crossbow", 2061002 },
	{ "Blue Arrow for Crossbow", 2061003 },
	{ "Diamond Arrow for Crossbow", 2061004 },
	{ "Subi Throwing-Stars", 2070000 },
	{ "Wolbi Throwing-Stars", 2070001 },
	{ "Mokbi Throwing-Stars", 2070002 },
	{ "Kumbi Throwing-Stars", 2070003 },
	{ "Tobi Throwing-Stars", 2070004 },
	{ "Steely Throwing-Knives", 2070005 },
	{ "Ilbi Throwing-Stars", 2070006 },
	{ "Hwabi Throwing-Stars", 2070007 },
	{ "Snowball", 2070008 },
	{ "Wooden Top", 2070009 },
	{ "Icicle", 2070010 },
	{ "Maple Throwing-Stars", 2070011 },
	{ "Paper Fighter Plane", 2070012 },
	{ "Orange", 2070013 },
	{ "Devil Rain Throwing Star", 2070014 },
	{ "A Beginner Thief's Throwing Stars", 2070015 },
	{ "Crystal Ilbi Throwing-Stars", 2070016 },
	{ "Balanced Fury", 2070018 },
	{ "Heart Megaphone", 2083000 },
	{ "Skull Megaphone", 2084000 },
	{ "Black Sack", 2100000 },
	{ "Monster Sack 1", 2100001 },
	{ "Monster Sack 2", 2100002 },
	{ "Monster Sack 3", 2100003 },
	{ "Monster Sack 4", 2100004 },
	{ "Monster Sack 5", 2100005 },
	{ "Monster Sack 6", 2100006 },
	{ "Monster Sack 7", 2100007 },
	{ "Summoning the Boss", 2100008 },
	{ "Summoning New-Type Balrog", 2100009 },
	{ "Summoning Dances with Balrog's Clone", 2100010 },
	{ "Summoning Grendel the Really Old's Clone", 2100011 },
	{ "Summoning Athena Pierce's Clone", 2100012 },
	{ "Summoning Dark Lord's Clone", 2100013 },
	{ "Brand New Monster Galore", 2100014 },
	{ "Summoning Bag of Birds", 2100015 },
	{ "Different Sack", 2100016 },
	{ "Alien Sack", 2100017 },
	{ "Toy Robot Sack", 2100018 },
	{ "Toy Trojan Sack", 2100019 },
	{ "Moon Sack", 2100020 },
	{ "Moon Sack", 2100021 },
	{ "Moon Sack", 2100022 },
	{ "Moon Sack", 2100023 },
	{ "Moon Sack", 2100024 },
	{ "Moon Sack", 2100025 },
	{ "Penalty Monster Sack 1", 2100026 },
	{ "Penalty Monster Sack 2", 2100027 },
	{ "Summoning Three-Tail Fox", 2100028 },
	{ "Summoning Ghosts", 2100029 },
	{ "Summoning Goblins", 2100030 },
	{ "Summoning Horntail A", 2100031 },
	{ "Summoning Horntail C", 2100032 },
	{ "Monster Sack 8", 2100033 },
	{ "Monster Sack 9", 2100034 },
	{ "Monster Sack 10", 2100035 },
	{ "Monster Sack 11", 2100036 },
	{ "Summon Master Monsters 1", 2100037 },
	{ "Summon Master Monsters 2", 2100038 },
	{ "Summon Master Monsters 3", 2100039 },
	{ "Summon Master Monsters 4", 2100040 },
	{ "Summoning Lord Pirate", 2100041 },
	{ "Summoning Peeking Lord Pirate", 2100042 },
	{ "Summoning Angry Lord Pirate", 2100043 },
	{ "Summoning Enraged Lord Pirate", 2100044 },
	{ "Summoning Lord Pirate's Jar", 2100045 },
	{ "Summoning Lord Pirate's Ginseng Jar", 2100046 },
	{ "Summoning Lord Pirate's Bellflower", 2100047 },
	{ "Summoning Lord Pirate's Old Bellflower", 2100048 },
	{ "Summoning Lord Pirate's Mr. Alli", 2100049 },
	{ "Summoning Lord Pirate's Kru", 2100050 },
	{ "Summoning Lord Pirate's Captain", 2100051 },
	{ "Moon Rabit Monster Sack", 2100052 },
	{ "Summon Romeo and Juliet PQ Mob", 2100053 },
	{ "Summon Romeo and Juliet PQ Mob", 2100054 },
	{ "Summon Romeo and Juliet PQ Mob", 2100055 },
	{ "Summon Romeo and Juliet PQ Mob", 2100056 },
	{ "Summon Romeo and Juliet PQ Mob", 2100057 },
	{ "Summon Romeo and Juliet PQ Mob", 2100058 },
	{ "Summon Romeo and Juliet PQ Mob", 2100059 },
	{ "Weird Sack", 2100060 },
	{ "Strange Sack", 2100061 },
	{ "Interesting Sack", 2100062 },
	{ "Summon Ghost", 2100063 },
	{ "Summon Ghost  2", 2100064 },
	{ "Summon Ghost  3", 2100065 },
	{ "Summon Slime", 2100066 },
	{ "Bombs for Hunting Competition", 2100067 },
	{ "Snowman Summon Sack", 2100068 },
	{ "Event Box", 2100069 },
	{ "1st Monster Marble", 2100070 },
	{ "Mu Lung Dojo Summon Package1_Mano", 2100071 },
	{ "Mu Lung Dojo Summon Package2_Stumpy", 2100072 },
	{ "Mu Lung Dojo Summon Package3_Deo", 2100073 },
	{ "Mu Lung Dojo Summon Package4_King Slime", 2100074 },
	{ "Mu Lung Dojo Summon Package5_Giant Centepede", 2100075 },
	{ "Mu Lung Dojo Summon Package6_Faust", 2100076 },
	{ "Mu Lung Dojo Summon Package7_King Clang", 2100077 },
	{ "Mu Lung Dojo Summon Package8_Mushroom", 2100078 },
	{ "Mu Lung Dojo Summon Package9_Alishar", 2100079 },
	{ "Mu Lung Dojo Summon Package10_Timer", 2100080 },
	{ "Mu Lung Dojo Summon Package11_Dyle", 2100081 },
	{ "Mu Lung Dojo Summon Package12_Papa Pixie", 2100082 },
	{ "Mu Lung Dojo Summon Package13_Zombie Mushroom", 2100083 },
	{ "Mu Lung Dojo Summon Package14_Zeno", 2100084 },
	{ "Mu Lung Dojo Summon Package15_Lord Pirate", 2100085 },
	{ "Mu Lung Dojo Summon Package16_Nine-Tailed Fox", 2100086 },
	{ "Mu Lung Dojo Summon Package17_Tae Room", 2100087 },
	{ "Mu Lung Dojo Summon Package18_Poison Golem", 2100088 },
	{ "Mu Lung Dojo Summon Package19_Priest Cat", 2100089 },
	{ "Mu Lung Dojo Summon Package20_Jr. Balrog", 2100090 },
	{ "Mu Lung Dojo Summon Package21_Elliza", 2100091 },
	{ "Mu Lung Dojo Summon Package22_Franken Lloyd", 2100092 },
	{ "Mu Lung Dojo Summon Package23_Kimera", 2100093 },
	{ "Mu Lung Dojo Summon Package24_Snack Bar", 2100094 },
	{ "Mu Lung Dojo Summon Package25_Snowman", 2100095 },
	{ "Mu Lung Dojo Summon Package26_Blue Mushroom", 2100096 },
	{ "Mu Lung Dojo Summon Package27_Crimson Balrog", 2100097 },
	{ "Mu Lung Dojo Summon Package28_Manon", 2100098 },
	{ "Mu Lung Dojo Summon Package29_Griffey", 2100099 },
	{ "Mu Lung Dojo Summon Package30_Leviathan", 2100100 },
	{ "Mu Lung Dojo Summon Package31_Papulatus", 2100101 },
	{ "Mu Lung Dojo Summon Package32_Moo Gong", 2100102 },
	{ "Mu Lung Dojo Summon Package00_So Gong", 2100103 },
	{ "Maple Ambush Sack", 2100104 },
	{ "Maze Snail Set", 2100105 },
	{ "Maze Transformation Snail Set", 2100106 },
	{ "Maze Transformation Snail Set2", 2100107 },
	{ "Master of Disguise Summoning Sack", 2100108 },
	{ "Black Witch Summoning Summoning Sack", 2100109 },
	{ "Blue Mushroom Summoning Sack", 2100110 },
	{ "Puppeteer Summoning Sack", 2100111 },
	{ "Summon Flying Monsters (Mark)", 2100112 },
	{ "Tristan's Balrog Summon", 2100113 },
	{ "Summon Maze Pigs", 2100116 },
	{ "Summon Maze Rash", 2100117 },
	{ "Dr. Kim's Anti-Virus Project", 2100118 },
	{ "Summons Maze Sand Bunny", 2100119 },
	{ "Snail Summoning Sack", 2100120 },
	{ "Slime Summoning Sack", 2100121 },
	{ "Green Mushroom Summoning Sack", 2100122 },
	{ "Octopus Summoning Sack", 2100123 },
	{ "Pig Summoning Sack", 2100124 },
	{ "Ribbon Pig Summoning Sack", 2100125 },
	{ "Orange Mushroom Summoning Sack", 2100126 },
	{ "Bubbling Summoning Sack", 2100127 },
	{ "Horny Mushroom Summoning Sack", 2100128 },
	{ "Jr. Necki Summoning Sack.", 2100129 },
	{ "Blue Mushroom Summoning Sack", 2100130 },
	{ "Tristan's Balrog Summoning Sack", 2100131 },
	{ "Balrog Summoning Sack", 2100132 },
	{ "Balrog's Spirit", 2100133 },
	{ "Rescued Gaga Summoning Sack", 2100134 },
	{ "Test MOB Summoning Sack", 2100135 },
	{ "Easy Mode Balrog Summoning Sack", 2100136 },
	{ "Easy Mode Balrog's Spirit", 2100137 },
	{ "Puppeteer Summoning Sack", 2100138 },
	{ "Puppeteer Summoning Sack", 2100139 },
	{ "Puppeteer Summong Sack", 2100140 },
	{ "Giant Summoning Sack", 2100152 },
	{ "Shadow Knight Summoning Sack", 2100153 },
	{ "Gentleman Summoning Sack", 2100154 },
	{ "Master of Disguise Summoning Sack", 2100155 },
	{ "Transformed Tru Summoning Sack", 2100159 },
	{ "Gray Yeti and King Pepe Summoning Bag", 2100160 },
	{ "Gold Yeti and King Pepe Summoning Bag", 2100161 },
	{ "White Yeti and King Pepe Summoning Bag", 2100162 },
	{ "Prime Minister Summoning Bag", 2100163 },
	{ "Black Wing Henchman Summoning Sack", 2100164 },
	{ "Hiver Summoning Sack", 2100165 },
	{ "Mysterious Sack", 2100900 },
	{ "Summoning Mushmom", 2101000 },
	{ "Summoning Crimson Balrog", 2101001 },
	{ "Summoning Werewolf", 2101002 },
	{ "Summoning Yeti & Pepe", 2101003 },
	{ "Summoning Superslime", 2101004 },
	{ "Summoning Tauromacis", 2101005 },
	{ "Summoning Taurospear", 2101006 },
	{ "Summoning Lycanthrope", 2101007 },
	{ "Summoning Dark Yeti & Pepe", 2101008 },
	{ "Summon Red Boogie", 2101009 },
	{ "Summon Blue Boogie", 2101010 },
	{ "Summon Green Boogie", 2101011 },
	{ "Summon Black Boogie", 2101012 },
	{ "Summon Showa Boss", 2101013 },
	{ "Summon Monsters", 2101014 },
	{ "Summon Bodyguard A", 2101015 },
	{ "Summon Toy Robot", 2101016 },
	{ "Summon Black Boogie", 2101017 },
	{ "Summon Black Boogie", 2101018 },
	{ "Summon Pachinko Monster", 2101019 },
	{ "Halloween Monster Sack", 2101020 },
	{ "Monster Sack (Jr. Mimick)", 2101021 },
	{ "Monster Sack (Golden Egg)", 2101022 },
	{ "Monster Sack (Slime Gold)", 2101023 },
	{ "Monster Sack (Slime Silver)", 2101024 },
	{ "Monster Sack (Slime Red)", 2101025 },
	{ "Monster Sack (Mushmom Blue)", 2101026 },
	{ "Monster Summoning Sack(Alishar)", 2101039 },
	{ "Amoria Penalty Monster Sack1", 2101043 },
	{ "Amoria Penalty Monster Sack2", 2101044 },
	{ "Amoria Penalty Monster Sack3", 2101045 },
	{ "Amoria Penalty Monster Sack4", 2101046 },
	{ "Amoria Penalty Monster Sack5", 2101047 },
	{ "Amoria Penalty Monster Sack6", 2101048 },
	{ "Amoria Penalty Monster Sack7", 2101049 },
	{ "GM event Sack1", 2101050 },
	{ "GM event Sack2", 2101051 },
	{ "GM event Sack3", 2101052 },
	{ "GM event Sack4", 2101053 },
	{ "GM event Sack5", 2101054 },
	{ "GM event Sack6", 2101055 },
	{ "GM event Sack7", 2101056 },
	{ "Amoria Penalty Monster Sack8", 2101057 },
	{ "Amoria Penalty Monster Sack8", 2101058 },
	{ "Monster Sack (SG CBD)", 2101060 },
	{ "Monster Sack (SG Ghost ship)", 2101061 },
	{ "Monster Sack", 2101072 },
	{ "Monster Sack", 2101073 },
	{ "Monster Sack(x-mas07_1)", 2101080 },
	{ "Monster Sack(x-mas07_2)", 2101081 },
	{ "Monster Sack(x-mas07_3)", 2101082 },
	{ "Monster Sack(x-mas07_4)", 2101083 },
	{ "Monster Sack(x-mas07_5)", 2101084 },
	{ "Monster Sack(x-mas07_6)", 2101085 },
	{ "Monster Sack(x-mas07_7)", 2101086 },
	{ "Monster Sack(x-mas07_8)", 2101087 },
	{ "Monster Sack(x-mas07_9)", 2101088 },
	{ "Monster Sack(x-mas07_10)", 2101089 },
	{ "Monster Sack(x-mas07_11)", 2101090 },
	{ "Monster Sack(x-mas07_12)", 2101091 },
	{ "Monster Sack(x-mas07_13)", 2101092 },
	{ "Monster Sack(x-mas07_14)", 2101093 },
	{ "Monster Summoning Sack(Leviathan)", 2101110 },
	{ "Giant Snowman (Lvl 1)", 2101124 },
	{ "Giant Snowman (Lvl 1)", 2101125 },
	{ "Giant Snowman (Lvl 1)", 2101126 },
	{ "Cross (Easy) Sack", 2101127 },
	{ "Cross (Medium) Sack", 2101128 },
	{ "Cross (Hard) Sack", 2101129 },
	{ "Summon Christmas Socks", 2101130 },
	{ "Summon Luck Sack", 2101131 },
	{ "Masteria Summoning Bag-Jungle Jam", 2101137 },
	{ "Masteria Summoning Bag-Corrupted Army", 2101138 },
	{ "Masteria Summoning Bag-Bosses", 2101139 },
	{ "MasteriaPQ Summon Bag1", 2101140 },
	{ "MasteriaPQ Summon Bag2", 2101141 },
	{ "MasteriaPQ Summon Bag3", 2101142 },
	{ "MasteriaPQ Summon Bag4", 2101143 },
	{ "MasteriaPQ Summon Bag5", 2101144 },
	{ "MasteriaPQ Summon Bag6", 2101145 },
	{ "MasteriaPQ Summon Bag7", 2101146 },
	{ "MasteriaPQ Summon Bag8", 2101147 },
	{ "MasteriaPQ Summon Bag9", 2101148 },
	{ "Big Puff Daddy Sack", 2101158 },
	{ "GMEvent_Horntail's Left Head", 2101200 },
	{ "GMEvent_Horntail's Right Head", 2101201 },
	{ "GMEvent_Pink Bean", 2101202 },
	{ "Suspicious Black Sack", 2101203 },
	{ "Olivia (30) Monster Sack", 2101204 },
	{ "Olivia (50) Monster Sack", 2101205 },
	{ "Olivia (70) Monster Sack", 2101206 },
	{ "A Parasite Summoning Sack", 2101207 },
	{ "Andras Summoning Sack", 2101208 },
	{ "Marbas Summoning Sack", 2101209 },
	{ "Amdusias Summoning Sack", 2101210 },
	{ "Valefor Summoning Sack", 2101211 },
	{ "Crocell Summoning Sack", 2101212 },
	{ "Astaroth Summoning Sack", 2101213 },
	{ "GMEvent_Pink Bean2", 2101236 },
	{ "Monster Attack Lvl 1", 2102000 },
	{ "Monster Attack Lvl 2", 2102001 },
	{ "Monster Attack Lvl 3", 2102002 },
	{ "Monster Attack Lvl 4", 2102003 },
	{ "Monster Attack Lvl 5", 2102004 },
	{ "Monster Attack Lvl 6", 2102005 },
	{ "Monster Attack Lvl 7", 2102006 },
	{ "Monster Attack Lvl 8", 2102007 },
	{ "Monster Attack Package 1", 2102008 },
	{ "Monster Attack Package 2", 2102009 },
	{ "Monster Marble", 2109000 },
	{ "1st Monster Marble", 2109001 },
	{ "2nd Monster Marble", 2109002 },
	{ "3rd Monster Marble", 2109003 },
	{ "Steal Sheep Wool", 2109004 },
	{ "Plant a Rose Thorn", 2109005 },
	{ "Pharaoh Yeti Summoning Bag", 2109006 },
	{ "Pharaoh Yeti Summoning Bag", 2109007 },
	{ "Bubbling Summoning Bag", 2109008 },
	{ "Jr. Yeti Pharaoh Summoning Bag", 2109009 },
	{ "Jr. Yeti Pharaoh Summoning Bag", 2109010 },
	{ "Pet Food", 2120000 },
	{ "Dry Treat", 2120008 },
	{ "New Year's Card", 2160101 },
	{ "Lie Detector Test", 2190000 },
	{ "Orange Mushroom Piece", 2210000 },
	{ "Ribbon Pig Piece", 2210001 },
	{ "Grey Piece", 2210002 },
	{ "Dragon Elixir", 2210003 },
	{ "Blue Ribbon Pig Piece", 2210004 },
	{ "Tigun Transformation Bundle.", 2210005 },
	{ "Rainbow-colored Snail Shell", 2210006 },
	{ "Change to Ghost", 2210007 },
	{ "Ghost Candy", 2210008 },
	{ "Sophillia's Abandoned Doll", 2210009 },
	{ "Potion of Transformation", 2210010 },
	{ "Potion of Transformation", 2210011 },
	{ "Change to Mouse", 2210012 },
	{ "Mini Draco Transformation", 2210016 },
	{ "Moon Photo", 2210017 },
	{ "Sweet Rice Cake", 2210018 },
	{ "Gaga Transformation Potion", 2210021 },
	{ "Peto Transformation Potion", 2210022 },
	{ "Cliff's Special Potion", 2210023 },
	{ "Maplemas Party Potion", 2210024 },
	{ "Geppetto Transformation", 2210030 },
	{ "Cody's Picture", 2210032 },
	{ "Cake Picture", 2210033 },
	{ "Alien Gray Transformation", 2210034 },
	{ "Penguin Transformation 1", 2210035 },
	{ "Penguin Transformation 2", 2210036 },
	{ "Penguin Transformation 3", 2210037 },
	{ "Penguin Transformation 4", 2210038 },
	{ "Penguin Transformation 5", 2210039 },
	{ "Leech Costume", 2210043 },
	{ "Cliff's Special Potion", 2211000 },
	{ "Maplemas Party Potion", 2212000 },
	{ "Moonstone Engagement Ring Box", 2240000 },
	{ "Star gem Engagement Ring Box", 2240001 },
	{ "Golden Heart Engagement Ring Box", 2240002 },
	{ "Silver Swan Engagement Ring Box", 2240003 },
	{ "Ring of Moon Stone", 2240004 },
	{ "Ring of Moon Stone: 2 Carats", 2240005 },
	{ "Ring of Moon Stone: 3 Carats", 2240006 },
	{ "Ring of Shining Star", 2240007 },
	{ "Ring of Shining Star: 2 Carats", 2240008 },
	{ "Ring of Shining Star: 3 Carats", 2240009 },
	{ "Gold Heart Ring", 2240010 },
	{ "Gold Heart Ring: 2 Carats", 2240011 },
	{ "Gold Heart Ring: 3 Carats", 2240012 },
	{ "Ring of Silver Wing", 2240013 },
	{ "Ring of Silver Wing: 2 Carats", 2240014 },
	{ "Ring of Silver Wing: 3 Carats", 2240015 },
	{ "Revitalizer", 2260000 },
	{ "Pheromone Perfume", 2270000 },
	{ "Pouch", 2270001 },
	{ "Element Rock", 2270002 },
	{ "Cliff's Magic Cane", 2270003 },
	{ "Purification Marble", 2270004 },
	{ "1st Transparent Marble", 2270005 },
	{ "2nd Transparent Marble", 2270006 },
	{ "3rd Transparent Marble", 2270007 },
	{ "Fish Net", 2270008 },
	{ "Red Ribbon Pig", 2270009 },
	{ "Green Ribbon Pig", 2270010 },
	{ "Blue Ribbon Pig", 2270011 },
	{ "Purple Ribbon Pig", 2270012 },
	{ "Lava Bottle", 2280000 },
	{ "Black Cloud Machine", 2280001 },
	{ "Firm Hand", 2280002 },
	{ "[Skill Book] Maple Hero", 2280003 },
	{ "[Skill Book] Infinity", 2280004 },
	{ "[Skill Book] Dragon's Breath", 2280005 },
	{ "[Skill Book] Taunt", 2280006 },
	{ "[Skill Book] Advanced Combo Attack", 2280007 },
	{ "[Skill Book] Advanced Charge", 2280008 },
	{ "[Skill Book] Angel Ray", 2280009 },
	{ "[Skill Book] Triple Throw", 2280010 },
	{ "Ancient Ice Powder", 2280011 },
	{ "[Skill Book] Rush", 2280012 },
	{ "[Skill Book] Final Blow", 2280013 },
	{ "[Skill Book] High Defense", 2280014 },
	{ "[Skill Book] Combo Tempest", 2280015 },
	{ "[Skill Book] Combo Barrier", 2280016 },
	{ "[Skill Book] Pig's Weakness", 2280017 },
	{ "[Skill Book] Stump's Weakness", 2280018 },
	{ "[Skill Book] Slime's Weakness", 2280019 },
	{ "[Mastery Book] Monster Magnet", 2290000 },
	{ "[Mastery Book] Monster Magnet", 2290001 },
	{ "[Mastery Book] Achilles", 2290002 },
	{ "[Mastery Book] Achilles", 2290003 },
	{ "[Mastery Book] Rush", 2290004 },
	{ "[Mastery Book] Rush", 2290005 },
	{ "[Mastery Book] Power Stance", 2290006 },
	{ "[Mastery Book] Power Stance", 2290007 },
	{ "[Mastery Book] Advanced Combo Attack", 2290008 },
	{ "[Mastery Book] Advanced Combo Attack", 2290009 },
	{ "[Mastery Book] Brandish", 2290010 },
	{ "[Mastery Book] Brandish", 2290011 },
	{ "[Mastery Book] Blast", 2290012 },
	{ "[Mastery Book] Blast", 2290013 },
	{ "[Mastery Book] Guardian", 2290014 },
	{ "[Mastery Book] Guardian", 2290015 },
	{ "[Mastery Book] Enrage", 2290016 },
	{ "[Mastery Book] Enrage", 2290017 },
	{ "[Mastery Book] Holy Charge", 2290018 },
	{ "[Mastery Book] Divine Charge", 2290019 },
	{ "[Mastery Book] Heaven's Hammer", 2290020 },
	{ "[Mastery Book] Heaven's Hammer", 2290021 },
	{ "[Mastery Book] Berserk", 2290022 },
	{ "[Mastery Book] Berserk", 2290023 },
	{ "[Mastery Book] Mana Reflection", 2290024 },
	{ "[Mastery Book] Mana Reflection", 2290025 },
	{ "[Mastery Book] Big Bang", 2290026 },
	{ "[Mastery Book] Big Bang", 2290027 },
	{ "[Mastery Book] Infinity", 2290028 },
	{ "[Mastery Book] Infinity", 2290029 },
	{ "[Mastery Book] Paralyze", 2290030 },
	{ "[Mastery Book] Paralyze", 2290031 },
	{ "[Mastery Book] Chain Lightning", 2290032 },
	{ "[Mastery Book] Chain Lightning", 2290033 },
	{ "[Mastery Book]  Holy Shield", 2290034 },
	{ "[Mastery Book] Holy Shield", 2290035 },
	{ "[Mastery Book] Fire Demon", 2290036 },
	{ "[Mastery Book] Fire Demon", 2290037 },
	{ "[Mastery Book] Elquines", 2290038 },
	{ "[Mastery Book] Elquines", 2290039 },
	{ "[Mastery Book] Meteor Shower", 2290040 },
	{ "[Mastery Book] Meteor Shower", 2290041 },
	{ "[Mastery Book] Ice Demon", 2290042 },
	{ "[Mastery Book] Ice Demon", 2290043 },
	{ "[Mastery Book] Ifrit", 2290044 },
	{ "[Mastery Book] Ifrit", 2290045 },
	{ "[Mastery Book] Blizzard", 2290046 },
	{ "[Mastery Book] Blizzard", 2290047 },
	{ "[Mastery Book] Genesis", 2290048 },
	{ "[Mastery Book] Genesis", 2290049 },
	{ "[Mastery Book] Angel Ray", 2290050 },
	{ "[Mastery Book] Angel Ray", 2290051 },
	{ "[Mastery Book] Sharp Eyes", 2290052 },
	{ "[Mastery Book] Sharp Eyes", 2290053 },
	{ "[Mastery Book] Dragon's Breath", 2290054 },
	{ "[Mastery Book] Dragon's Breath", 2290055 },
	{ "[Mastery Book] Bow Expert", 2290056 },
	{ "[Mastery Book] Bow Expert", 2290057 },
	{ "[Mastery Book] Hamstring Shot", 2290058 },
	{ "[Mastery Book] Hamstring Shot", 2290059 },
	{ "[Mastery Book] Hurricane", 2290060 },
	{ "[Mastery Book] Hurricane", 2290061 },
	{ "[Mastery Book] Phoenix", 2290062 },
	{ "[Mastery Book] Phoenix", 2290063 },
	{ "[Mastery Book] Concentrate", 2290064 },
	{ "[Mastery Book] Concentrate", 2290065 },
	{ "[Mastery Book] Marksman Boost", 2290066 },
	{ "[Mastery Book] Marksman Boost", 2290067 },
	{ "[Mastery Book] Blind", 2290068 },
	{ "[Mastery Book] Blind", 2290069 },
	{ "[Mastery Book] Piercing Arrow", 2290070 },
	{ "[Mastery Book] Piercing Arrow", 2290071 },
	{ "[Mastery Book] Frostprey", 2290072 },
	{ "[Mastery Book] Frostprey", 2290073 },
	{ "[Mastery Book] Snipe", 2290074 },
	{ "[Mastery Book] Snipe", 2290075 },
	{ "[Mastery Book] Shadow Shifter", 2290076 },
	{ "[Mastery Book] Shadow Shifter", 2290077 },
	{ "[Mastery Book] Venomous Star/Venomous Stab", 2290078 },
	{ "[Mastery Book] Venomous Star/Venomous Stab", 2290079 },
	{ "[Mastery Book] Taunt", 2290080 },
	{ "[Mastery Book] Taunt", 2290081 },
	{ "[Mastery Book] Ninja Ambush", 2290082 },
	{ "[Mastery Book] Ninja Ambush", 2290083 },
	{ "[Mastery Book] Triple Throw", 2290084 },
	{ "[Mastery Book] Triple Throw", 2290085 },
	{ "[Mastery Book] Ninja Storm", 2290086 },
	{ "[Mastery Book] Ninja Storm", 2290087 },
	{ "[Mastery Book] Shadow Claw", 2290088 },
	{ "[Mastery Book] Shadow Claw", 2290089 },
	{ "[Mastery Book] Boomerang Step", 2290090 },
	{ "[Mastery Book] Boomerang Step", 2290091 },
	{ "[Mastery Book] Assassinate", 2290092 },
	{ "[Mastery Book] Assassinate", 2290093 },
	{ "[Mastery Book] Smokescreen", 2290094 },
	{ "[Mastery Book] Smokescreen", 2290095 },
	{ "[Mastery Book] Maple Hero 20", 2290096 },
	{ "[Mastery Book] Dragon Strike", 2290097 },
	{ "[Mastery Book] Dragon Strike", 2290098 },
	{ "[Mastery Book] Energy Orb", 2290099 },
	{ "[Mastery Book] Energy Orb", 2290100 },
	{ "[Mastery Book] Super Transformation", 2290101 },
	{ "[Mastery Book] Demolition", 2290102 },
	{ "[Mastery Book] Demolition", 2290103 },
	{ "[Mastery Book] Snatch", 2290104 },
	{ "[Mastery Book] Snatch", 2290105 },
	{ "[Mastery Book] Barrage", 2290106 },
	{ "[Mastery Book] Barrage", 2290107 },
	{ "[Mastery Book] Speed Infusion", 2290108 },
	{ "[Mastery Book] Wind Booster", 2290109 },
	{ "[Mastery Book] Time Leap", 2290110 },
	{ "[Mastery Book] Time Leap", 2290111 },
	{ "[Mastery Book] Elemental Boost", 2290112 },
	{ "[Mastery Book] Elemental Boost", 2290113 },
	{ "[Mastery Book] Wrath of the Octopi", 2290114 },
	{ "[Mastery Book] Air Strike", 2290115 },
	{ "[Mastery Book] Air Strike", 2290116 },
	{ "[Mastery Book] Rapid Fire", 2290117 },
	{ "[Mastery Book] Rapid Fire", 2290118 },
	{ "[Mastery Book] Battleship Cannon", 2290119 },
	{ "[Mastery Book] Battleship Cannon", 2290120 },
	{ "[Mastery Book] Battleship Torpedo", 2290121 },
	{ "[Mastery Book] Battleship Torpedo", 2290122 },
	{ "[Mastery Book] Hypnotize", 2290123 },
	{ "[Mastery Book] Bullseye", 2290124 },
	{ "[Mastery Book] Maple Hero 30", 2290125 },
	{ "[Mastery Book] Overswing 20", 2290126 },
	{ "[Mastery Book] Overswing 30", 2290127 },
	{ "[Mastery Book] High Mastery 20", 2290128 },
	{ "[Mastery Book]High Mastery 30", 2290129 },
	{ "[Mastery Book] Freeze Standing 20", 2290130 },
	{ "[Mastery Book] Freeze Standing 30", 2290131 },
	{ "[Mastery Book] Final Blow 20", 2290132 },
	{ "[Mastery Book] Final Blow 30", 2290133 },
	{ "[Mastery Book] High Defense 20", 2290134 },
	{ "[Mastery Book] High Defense 30", 2290135 },
	{ "[Mastery Book] Combo Tempest 20", 2290136 },
	{ "[Mastery Book] Combo Tempest 30", 2290137 },
	{ "[Mastery Book] Combo Barrier 20", 2290138 },
	{ "[Mastery Book] Combo Barrier 30", 2290139 },
	{ "The Owl of Minerva", 2310000 },
	{ "Teleport Rock", 2320000 },
	{ "Bullet", 2330000 },
	{ "Split Bullet", 2330001 },
	{ "Mighty Bullet", 2330002 },
	{ "Vital Bullet", 2330003 },
	{ "Shiny Bullet", 2330004 },
	{ "Eternal Bullet", 2330005 },
	{ "Bullet for Novice Pirates", 2330006 },
	{ "Blaze Capsule", 2331000 },
	{ "Glaze Capsule", 2332000 },
	{ "White Scroll", 2340000 },
	{ "Change to Ghost", 2360000 },
	{ "Ghost Candy", 2360001 },
	{ "Board the Spaceship", 2360002 },
	{ "The Songs of Solomon", 2370000 },
	{ "The Stories of Solomon", 2370001 },
	{ "The Travels of Solomon", 2370002 },
	{ "The Writs of Solomon X", 2370003 },
	{ "The Writs of Solomon IX", 2370004 },
	{ "The Writs of Solomon VIII", 2370005 },
	{ "The Writs of Solomon VII", 2370006 },
	{ "The Writs of Solomon VI", 2370007 },
	{ "The Writs of Solomon V", 2370008 },
	{ "The Writs of Solomon IV", 2370009 },
	{ "The Writs of Solomon III", 2370010 },
	{ "The Writs of Solomon II", 2370011 },
	{ "The Writs of Solomon I", 2370012 },
	{ "Snail Card", 2380000 },
	{ "Blue Snail Card", 2380001 },
	{ "Spore Card", 2380002 },
	{ "Stump Card", 2380003 },
	{ "Red Snail Card", 2380004 },
	{ "Slime Card", 2380005 },
	{ "Pig Card", 2380006 },
	{ "Orange Mushroom Card", 2380007 },
	{ "Dark Stump Card", 2380008 },
	{ "Ribbon Pig Card", 2380009 },
	{ "Octopus Card", 2380010 },
	{ "Green Mushroom Card", 2380011 },
	{ "Bubbling Card", 2380012 },
	{ "Cynical Orange Mushroom Card", 2380013 },
	{ "Dejected Green Mushroom Card", 2380014 },
	{ "Muru Card", 2380015 },
	{ "Murupa Card", 2380016 },
	{ "Murupia Card", 2380017 },
	{ "MuruMuru Card", 2380018 },
	{ "Murukun Card", 2380019 },
	{ "Axe Stump Card", 2381000 },
	{ "Ghost Stump Card", 2381001 },
	{ "Blue Mushroom Card", 2381002 },
	{ "Stirge Card", 2381003 },
	{ "Female Desert Rabbit Card", 2381004 },
	{ "Male Desert Rabbit Card", 2381005 },
	{ "Jr. Necki Card", 2381006 },
	{ "Horny Mushroom Card", 2381007 },
	{ "Dark Axe Stump Card", 2381008 },
	{ "Pinboom Card", 2381009 },
	{ "Jr. Cactus Card", 2381010 },
	{ "Trixter Card", 2381011 },
	{ "Jr. Sentinel Card", 2381012 },
	{ "Seacle Card", 2381013 },
	{ "Wooden Mask Card", 2381014 },
	{ "Bellamoa Card", 2381015 },
	{ "Zombie Mushroom Card", 2381016 },
	{ "Krappy Card", 2381017 },
	{ "Rocky Mask Card", 2381018 },
	{ "Ear Plug Plead Card", 2381019 },
	{ "Sand Rat Card", 2381020 },
	{ "Cico Card", 2381021 },
	{ "Wild Boar Card", 2381022 },
	{ "Cactus Card", 2381023 },
	{ "Evil Eye Card", 2381024 },
	{ "Scarf Plead Card", 2381025 },
	{ "Bubble Fish Card", 2381026 },
	{ "Green Trixter Card", 2381027 },
	{ "Royal Cactus Card", 2381028 },
	{ "Flower Fish Card", 2381029 },
	{ "Meercat Card", 2381030 },
	{ "Scorpion Card", 2381031 },
	{ "Sentinel Card", 2381032 },
	{ "Fairy Card", 2381033 },
	{ "Brown Teddy Card", 2381034 },
	{ "Krip Card", 2381035 },
	{ "Kiyo Card", 2381036 },
	{ "Ice Sentinel Card", 2381037 },
	{ "Fire Sentinel Card", 2381038 },
	{ "Smiling Ghost Stump Card", 2381082 },
	{ "Annoyed Zombie Mushroom Card", 2381083 },
	{ "Chirppy Card", 2382000 },
	{ "Drum Bunny Card", 2382001 },
	{ "Ligator Card", 2382002 },
	{ "Fireboar Card", 2382003 },
	{ "Pink Teddy Card", 2382004 },
	{ "Ratz Card", 2382005 },
	{ "Leatty Card", 2382006 },
	{ "Mask Fish Card", 2382007 },
	{ "Sand Dwarf Card", 2382008 },
	{ "Cube Slime Card", 2382009 },
	{ "Red Sand Dwarf Card", 2382010 },
	{ "Jr. Cellion Card", 2382011 },
	{ "Jr. Lioner Card", 2382012 },
	{ "Jr. Grupin Card", 2382013 },
	{ "Dark Leatty Card", 2382014 },
	{ "Roloduck Card", 2382015 },
	{ "Black Ratz Card", 2382016 },
	{ "Tick Card", 2382017 },
	{ "Curse Eye Card", 2382018 },
	{ "Jr. Wraith Card", 2382019 },
	{ "Star Pixie Card", 2382020 },
	{ "Jr. Boogie Card", 2382021 },
	{ "Bloctopus Card", 2382022 },
	{ "Jr. Pepe Card", 2382023 },
	{ "Rumo Card", 2382024 },
	{ "Panda Teddy Card", 2382025 },
	{ "Helly Card", 2382026 },
	{ "Scuba Pepe Card", 2382027 },
	{ "Retz", 2382028 },
	{ "Lupin Card", 2382029 },
	{ "Lorang Card", 2382030 },
	{ "Propelly Card", 2382031 },
	{ "Chronos Card", 2382032 },
	{ "King Bloctopus Card", 2382033 },
	{ "Planey Card", 2382034 },
	{ "Jr. Seal Card", 2382035 },
	{ "Triple Rumo Card", 2382036 },
	{ "Tweeter Card", 2382037 },
	{ "Toy Trojan Card", 2382038 },
	{ "Cold Eye Card", 2382039 },
	{ "Zombie Lupin Card", 2382040 },
	{ "Tick-Tock Card", 2382041 },
	{ "Barnard Grey Card", 2382042 },
	{ "Poopa Card", 2382043 },
	{ "Poison Poopa Card", 2382044 },
	{ "Chipmunk Card", 2382045 },
	{ "Desert Giant Card", 2382046 },
	{ "Flyeye", 2382047 },
	{ "Robo Card", 2382048 },
	{ "Platoon Chronos Card", 2382049 },
	{ "Mateon Card", 2382050 },
	{ "Red Porky Card", 2382051 },
	{ "Nependeath Card", 2382052 },
	{ "Iron Hog Card", 2382053 },
	{ "Block Golem", 2382054 },
	{ "Zeta Grey Card", 2382055 },
	{ "Freezer Card", 2382056 },
	{ "Iron Mutae", 2382057 },
	{ "Jr. Cerebes Card", 2382058 },
	{ "Sparker Card", 2382059 },
	{ "Black Porky Card", 2382060 },
	{ "Plateon Card", 2382061 },
	{ "Master Robo Card", 2382062 },
	{ "Skeledog Card", 2382063 },
	{ "Lunar Pixie Card", 2382064 },
	{ "Copper Drake Card", 2382065 },
	{ "King Block Golem Card", 2382066 },
	{ "Ultra Grey Card", 2382067 },
	{ "Moon Bunny Card", 2382068 },
	{ "Iron Boar Card", 2382069 },
	{ "Blue Flower Serpent", 2382070 },
	{ "Red Flower Serpent", 2382071 },
	{ "Reinforced Iron Mutae", 2382072 },
	{ "Mossy Snail Card", 2382076 },
	{ "Renegade Spore Card", 2382092 },
	{ "Poison Mushroom Card", 2382093 },
	{ "Intoxicated Pig Card", 2382094 },
	{ "Helmet Pepe Card", 2382095 },
	{ "Royal Guard Pepe Card", 2382096 },
	{ "Mecateon Card", 2383000 },
	{ "Tortie Card", 2383001 },
	{ "Master Chronos Card", 2383002 },
	{ "Dark Nependeath Card", 2383003 },
	{ "Rombot Card", 2383004 },
	{ "Mummy Dog Card", 2383005 },
	{ "Jar Card", 2383006 },
	{ "Mithril Mutae Card", 2383007 },
	{ "Wraith Card", 2383008 },
	{ "Clang Card", 2383009 },
	{ "Ginseng Jar", 2383010 },
	{ "Chief Grey Card", 2383011 },
	{ "Drake Card", 2383012 },
	{ "Jr. Yeti Card", 2383013 },
	{ "Hodori Card", 2383014 },
	{ "Straw Target Dummy", 2383015 },
	{ "Reinforced Mithril Mutae", 2383016 },
	{ "Firebomb Card", 2383017 },
	{ "Wooden Target Dummy", 2383018 },
	{ "Croco Card", 2383019 },
	{ "Luster Pixe Card", 2383020 },
	{ "Cellion Card", 2383021 },
	{ "Lioner Card", 2383022 },
	{ "Grupin Card", 2383023 },
	{ "Hogul", 2383024 },
	{ "Bellflower Root Card", 2383025 },
	{ "MT-09 Card", 2383026 },
	{ "Sr. Bellflower Root Card", 2383027 },
	{ "Roid Card", 2383028 },
	{ "Malady Card", 2383029 },
	{ "Stone Golem Card", 2383030 },
	{ "Hector Card", 2383031 },
	{ "The Book Ghost Card", 2383032 },
	{ "Dark Jr. Yeti Card", 2383033 },
	{ "Tri-Tailed Fox Card", 2383034 },
	{ "Grizzly Card", 2383035 },
	{ "Skeleton Soldier", 2383036 },
	{ "Coolie Zombie Card", 2383037 },
	{ "Miner Zombie", 2383038 },
	{ "Dark Stone Golem", 2383039 },
	{ "White Fang Card", 2383040 },
	{ "Reindeer Card", 2383041 },
	{ "Neo Huroid Card", 2383042 },
	{ "Mixed Golem Card", 2383043 },
	{ "Red Drake Card", 2383044 },
	{ "Pepe Card", 2383045 },
	{ "Blin Card", 2383046 },
	{ "Panda Card", 2383047 },
	{ "Shade Card", 2383048 },
	{ "Master Dummy Card", 2383049 },
	{ "Tree Rod Card", 2383056 },
	{ "Mossy Mushroom Card", 2383057 },
	{ "Primitive Boar Card", 2383058 },
	{ "Stone Bug Card", 2383059 },
	{ "Buffy Card", 2384000 },
	{ "Wild Cargo Card", 2384001 },
	{ "Peach Monkey Card", 2384002 },
	{ "Officer Skeleton Card", 2384003 },
	{ "Soul Teddy Card", 2384004 },
	{ "Jr. Luinel Card", 2384005 },
	{ "Ice Drake Card", 2384006 },
	{ "Dark Pepe Card", 2384007 },
	{ "Mr. Alli Card", 2384008 },
	{ "Yeti Card", 2384009 },
	{ "Riche Card", 2384010 },
	{ "Homun Card", 2384011 },
	{ "Lazy Buffy Card", 2384012 },
	{ "Sage Cat Card", 2384013 },
	{ "Master Soul Teddy Card", 2384014 },
	{ "Dark Drake Card", 2384015 },
	{ "Dark Yeti Card", 2384016 },
	{ "Kru Card", 2384017 },
	{ "Cyti Card", 2384018 },
	{ "Klock Card", 2384019 },
	{ "Tauromacis Card", 2384020 },
	{ "Yellow King Goblin Card", 2384021 },
	{ "Blue King Goblin Card", 2384022 },
	{ "Green King Goblin Card", 2384023 },
	{ "Rash Card", 2384024 },
	{ "Captain Card", 2384025 },
	{ "Cerebes Card", 2384026 },
	{ "Beetle Card", 2384027 },
	{ "Hobi Card", 2384028 },
	{ "Commander Skeleton Card", 2384029 },
	{ "Luinel Card", 2384030 },
	{ "Homunculu Card", 2384031 },
	{ "Buffoon Card", 2384032 },
	{ "Dark Rash Card", 2384033 },
	{ "D.Roy Card", 2384034 },
	{ "Werewolf Card", 2384035 },
	{ "Taurospear Card", 2384036 },
	{ "Snow Witch Card", 2384037 },
	{ "Security Camera Card", 2384038 },
	{ "Scholar Ghost Card", 2384039 },
	{ "Rurumo Card", 2384040 },
	{ "Dark Klock Card", 2385000 },
	{ "Dual Beetle Card", 2385001 },
	{ "Green Hobi Card", 2385002 },
	{ "Deep Buffoon Card", 2385003 },
	{ "Yeti and Pepe Card", 2385004 },
	{ "Hankie Card", 2385005 },
	{ "Lycanthrope Card", 2385006 },
	{ "Harp Card", 2385007 },
	{ "Homunscullo Card", 2385008 },
	{ "Dark Yeti and Pepe Card", 2385009 },
	{ "Pirate Card", 2385010 },
	{ "Blood Harp Card", 2385011 },
	{ "Death Teddy Card", 2385012 },
	{ "Goby Card", 2385013 },
	{ "Birk Card", 2385014 },
	{ "Dual Pirate Card", 2385015 },
	{ "Black Kentaurus Card", 2385016 },
	{ "Red Kentaurus Card", 2385017 },
	{ "Blue Kentaurus Card", 2385018 },
	{ "Dual Birk Card", 2385019 },
	{ "Master Death Teddy Card", 2385020 },
	{ "Bain Card", 2385021 },
	{ "Blue Dragon Turtle Card", 2385022 },
	{ "Deet and Roi Card", 2385023 },
	{ "Eye of Time Card", 2385025 },
	{ "Bone Fish Card", 2386000 },
	{ "Red Dragon Turtle Card", 2386001 },
	{ "Viking Card", 2386002 },
	{ "Squid Card", 2386003 },
	{ "Phantom Watch Card", 2386004 },
	{ "Rexton Card", 2386005 },
	{ "Brexton Card", 2386006 },
	{ "Risell Squid Card", 2386007 },
	{ "Red Wyvern Card", 2386008 },
	{ "Gigantic Viking Card", 2386009 },
	{ "G. Phantom Watch Card", 2386010 },
	{ "Green Cornian Card", 2386011 },
	{ "Shark Card", 2386012 },
	{ "Blue Wyvern Card", 2386013 },
	{ "Cold Shark Card", 2386014 },
	{ "Dark Wyvern Card", 2386015 },
	{ "Dark Cornian Card", 2386016 },
	{ "Jr. Newtie Card", 2386017 },
	{ "Memory Monk Card", 2386021 },
	{ "Memory Monk Trainee Card", 2386022 },
	{ "Memory Guardian Card", 2386023 },
	{ "Chief Memory Guardian Card", 2386024 },
	{ "Gatekeeper Card", 2387000 },
	{ "Thanatos Card", 2387001 },
	{ "Skelegon Card", 2387002 },
	{ "Skelosaurus Card", 2387003 },
	{ "Nest Golem Card", 2387004 },
	{ "Qualm Monk Card", 2387006 },
	{ "Qualm Monk Trainee Card", 2387007 },
	{ "Qualm Guardian Card", 2387008 },
	{ "Chief Qualm Guardian Card", 2387009 },
	{ "Oblivion Monk Card", 2387010 },
	{ "Oblivion Monk Trainee Card", 2387011 },
	{ "Oblivion Guardian Card", 2387012 },
	{ "Chief Oblivion Guardian Card", 2387013 },
	{ "Mano Card", 2388000 },
	{ "King Slime Card", 2388001 },
	{ "Faust Card", 2388002 },
	{ "King Clang Card", 2388003 },
	{ "Alishar Card", 2388004 },
	{ "Timer Card", 2388005 },
	{ "Mushmom Card", 2388006 },
	{ "Dyle Card", 2388007 },
	{ "Zombie Mushmom", 2388008 },
	{ "Nine-Tailed Fox Card", 2388009 },
	{ "Tae Roon Card", 2388010 },
	{ "Lord Pirate Card", 2388011 },
	{ "Papa Pixie Card", 2388012 },
	{ "King Sage Cat Card", 2388013 },
	{ "Frankenroid Card", 2388014 },
	{ "Elliza Card", 2388015 },
	{ "Snowman Card", 2388016 },
	{ "Crimson Balrog Card", 2388017 },
	{ "Manon Card", 2388018 },
	{ "Griffey Card", 2388019 },
	{ "Pianus Card", 2388020 },
	{ "Ergoth Card", 2388021 },
	{ "Papulatus Card", 2388022 },
	{ "Zakum Card", 2388023 },
	{ "Horned Tail Card", 2388024 },
	{ "Stumpy Card", 2388025 },
	{ "Jr. Balrog Card", 2388026 },
	{ "Rudolph Card", 2388027 },
	{ "Kid Snowman Card", 2388028 },
	{ "Deo Card", 2388029 },
	{ "Seruf Card", 2388030 },
	{ "Zeno Card", 2388031 },
	{ "Kimera Card", 2388032 },
	{ "Leviathan Card", 2388033 },
	{ "Poison Golme Card", 2388039 },
	{ "Dodo Card", 2388040 },
	{ "Lilynouch Card", 2388041 },
	{ "Lyka Card", 2388042 },
	{ "Pink Bean", 2388043 },
	{ "Mu Gong Card", 2388046 },
	{ "Giant Centipede Card", 2388052 },
	{ "Blue Mushmom Card", 2388053 },
	{ "Snack Bar Card", 2388054 },
	{ "Balrog Card", 2388055 },
	{ "Gray Yeti and King Pepe Card", 2388067 },
	{ "Gold Yeti and King Pepe Card", 2388068 },
	{ "White Yeti and King Pepe Card", 2388069 },
	{ "Prime Minister Mushroom Card", 2388070 },
	{ "Helena's Marble", 2390000 },
	{ "Torn Cygnus' Book Volume 1", 2430000 },
	{ "Torn Cygnus' Book Volume 2", 2430001 },
	{ "Torn Cygnus' Book Volume 3", 2430002 },
	{ "Cygnus Quiz", 2430003 },
	{ "Richie Gold's Random Key Pot", 2430004 },
	{ "Memorial Map", 2430005 },
	{ "Mysterious Piece of Paper", 2430006 },
	{ "Empty Compass", 2430007 },
	{ "Golden Compass", 2430008 },
	{ "Pure Perfume", 2430009 },
	{ "Mysterious Artifact", 2430010 },
	{ "Agent Summon", 2430011 },
	{ "Agent Removal", 2430012 },
	{ "Peng Peng Popsicle", 2430013 },
	{ "Killer Mushroom Spore", 2430014 },
	{ "Thorn Remover", 2430015 },
	{ "Crystal Chest", 2430016 },
	{ "Mystery Box ", 2430026 },
	{ "Mystery Box ", 2430027 },
	{ "Mystery Box ", 2430028 },
	{ "Mystery Box ", 2430029 },
	{ "Golden Compass", 2430030 },
	{ "Instant Camera", 2430031 },
	{ "Black Bag", 2430032 },
	{ "Richie Gold's Fake Lead", 2440000 },
	{ "Hunter's Luck", 2450000 },
	});

	return useItems;
}

static void FindItemInMap(String^ itemStr, std::unordered_map<std::string, int> mapToIter) {
	if (itemStr[0].IsLower(itemStr[0])) {
		toupper(itemStr[0]);
	}
	const std::string iStr = ConvertSystemToStdStr(itemStr);
	// Iterator finds if an element with key "" exists or not.
	const auto iterator = mapToIter.find(iStr);
	// Check if iterator points to end of map
	if (iterator != mapToIter.end()) {
		Log::WriteLineToConsole("Found USE item!");
		const auto itemName = iterator->first;
		const auto itemId = iterator->second;
		Log::WriteLineToConsole("Name: " + ConvertStdToSystemStr(itemName) + " :: ID: " + ConvertStdToSystemStr(std::to_string(itemId)));
	}
	else {
		Log::WriteLineToConsole("USE item not found!");
	}
}

static void GetToPathOfTimeFromInside(int mapID) {
	switch (mapID) {
	case 220060000: // Warped path of time 1
		Teleport(-240, -85); // portal
		// press key up or send packet
		// wait 500-1000ms
		break;

	case 220060100: // Warped path of time 2
		Teleport(-336, 1157); // portal
		// press key up or send packet
		// wait 500-1000ms
		if (PointerFuncs::getMapID() == 220060000) {
			Teleport(-240, -85); // portal
			// press key up or send packet
			// wait 500-1000ms
		}
		else Log::WriteLineToConsole("Error failed to enter mapID 220060000!");
		break;

	case 220060200: // Warped path of time 3
		Teleport(-818, -102); // portal
			// press key up or send packet
			// wait 500-1000ms
		if (PointerFuncs::getMapID() == 220060100) {
			Teleport(-336, 1157); // portal
			// press key up or send packet
			// wait 500-1000ms
			if (PointerFuncs::getMapID() == 220060000) {
				Teleport(-240, -85); // portal
				// press key up or send packet
				// wait 500-1000ms
			}
		}
		break;

		default:;
	}

}