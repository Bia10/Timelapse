#pragma once
#include "Structs.h"

/*  
 *  Addresses defined here were found using the following programs: Cheat Engine, Hex-Rays IDA, ReClassEx
 *  Default Image Base Address for a 32-bit exe in Windows, when loaded into Memory is 0x400000
 *  So all the addresses defined here already have 0x400000 added for convenience purposes 
 *  These addresses are all virtual addresses defined in MapleStory.exe's virtual address space
 */

#pragma region Hack Adresses
// MAIN TAB REGION
ULONG logoSkipAddr = 0x0062F2D6;

// HACK TAB REGION 
ULONG fullGodmodeAddr = 0x009581D5;
ULONG missGodmodeAddr = 0x009582E9;
ULONG blinkGodmodeAddr = 0x00932501;
ULONG swimInAirAddr = 0x00704704;
ULONG unlimitedAttackAddr = 0x009536E0; 
ULONG fullAccuracyAddr = 0x00AFE7F8; //Client sided only version?? This is incomplete acc hack.
ULONG noBreathAddr = 0x00452316; //Fake/imperfect no breath?
ULONG noPlayerKnocbackAddr = 0x007A637F;
ULONG noPlayerDeathAddr = 0x009506C6;
ULONG jumpDownAnywhereAddr = 0x0094C6EE;
ULONG noSkillEffectAddr = 0x00933990;
ULONG noAttackDelayAddr = 0x0092EDB2;
ULONG noPlayerNameTagAddr = 0x00942DCC;
ULONG attackDelayAddr = 0x00454795;
ULONG instantDropItemsAddr = 0x00AF0E1C;
ULONG instantLootItemsAddr = 0x004417E3;
ULONG tubiAddr = 0x00485C01;
ULONG noMobReactionAddr = 0x0066B05E;
ULONG noMobDeathEffectAddr = 0x00663995;
ULONG noMobKnockbackAddr = 0x00668C9E;
ULONG mobDisarmAddr = 0x00667A00;
ULONG noMapBackgroundAddr = 0x00639CB6;
ULONG noMapObjectsAddr = 0x00639CAF;
ULONG noMapTitlesAddr = 0x00639CA8;
ULONG noMapFadeEffect = 0x00776E65;
ULONG mapSpeedUpAddr = 0x009B21A0;
ULONG removeSpamFilterAddr1 = 0x00490607; 
ULONG removeSpamFilterAddr2 = 0x00490651;
ULONG infiniteChatboxAddr1 = 0x004CAA09;
ULONG infiniteChatboxAddr2 = 0x004CAA84;
ULONG noBlueBoxesAddr = 0x009929DD;
ULONG walkingFrictionAddr = 0x009B4365; // je -> jne

// VAC TAB REGION
ULONG fullMapAttackAddr = 0x006785CA;
ULONG zzVacAddr1 = 0x009B17A0; 
ULONG zzVacAddr2 = 0x009B17B0;
ULONG vacForceRightAddr = 0x009B2C1E; // jae -> jna	
ULONG vacRightNoForce = 0x009B2C32; // jae -> jna
ULONG vacJumpLeftAddr = 0x009B4632; // jae -> je
ULONG vacJumpRightAddr = 0x009B46A1; // jna -> je		
ULONG vacJumpUpAddr = 0x009B4732; // jae -> je	
ULONG vacLeftAddr = 0x009B4819;  // jae -> je	
ULONG vacRightAddr= 0x009B4896; // jbe -> je	
ULONG fangorVacAddr1 = 0x009B2B98; // fld(0) -> fld(1) //vac into left wall		
ULONG fangorVacAddr2 = 0x009B43BE; // fld(0) -> fld(1) //vac into top left corner		
ULONG pVacAddr = 0x009B1E43; // codecave

// NOT YET IMPLEMENTED?
ULONG multiClientAddr = 0x00949BC7; // jne -> jmp
ULONG lagHackAddr = 0x009B16F2; // je -> jne
ULONG accuracyHackAddr1 = 0x00424D22; // codecave
ULONG accuracyHackAddr2 = 0x00AFE7F8; // codecave
ULONG accuracyHackAddr3 = 0x005E2AAA; // codecave
ULONG mpRegenTickTimeAddr = 0x00A031F5; // cmp ebx,00002710 -> cmp ebx, [BYTE_VALUE]
ULONG sitAnywhereAddr = 0x009506E9; // je -> 2x nop
ULONG speedWalkAddr = 0x009B268D; // je -> 6x nop
ULONG mouseCSEAXVacYAddr = 0x009B6352; // codecave
ULONG mouseCSEAXVacXAddr = 0x009B62ED; // codecave
ULONG mesoDropCap = 0x0081DAC7; // 4 bytes
ULONG magicAttCap = 0x00780621; // 4 bytes
ULONG gravity = 0x00AF0DE0; // double
ULONG bringYourOwnRopeAddr = 0x00A45B03; // codecave
ULONG MSCRCBypassAddr1 = 0x004A27E7; // codecave
ULONG MSCRCBypassAddr2 = 0x004A27EC; // codecave
ULONG slideRightAddr = 0x009B2C0A; // jna -> jne
ULONG itsRainingMobsAddr = 0x009B1E8E; // F1 -> F2, bugged diassembly??
ULONG attackUnrandommizerAddr = 0x0076609C; // codecave
ULONG etcExplosionAddr = 0x00505806; // 6x nop
ULONG useRechargableItemsAfterDepletionAddr1 = 0x009516BA; // 6x nop
ULONG useRechargableItemsAfterDepletionAddr2 = 0x009516C2; // je -> jns
ULONG chargeSkillsNoChargingAddr1 = 0x009B2154; //jne -> jmp		
// ULONG chargeSkillsNoChargingAddr2 = ??????????		
ULONG noJumpingMobAndPlayerAddr = 0x009B44D4; //je -> jmp		
ULONG vacLeftAddr2 = 0x009B2441; //??		
ULONG jmpRelatedstub = 0x009B2BF7; //??		
ULONG gravityrelated = 0x009B2BF5; //jae -> jmp for monster fly up on jump
ULONG mapGlideAddr = 0x009B2BE8; // jna 009B2C11 jna->jae monsters/players glide like in Elnath

// OLDSKOOL STUFF
// pin typer v0.62 004A0A6B: //83 FA 6F 0F 86 ?? ?? ?? ?? 83 FA 7B 
// jbe -> je
// take one dmg v0.62 00670090: // DF E0 9E 72 04 DD D8 D9 E8 DC 15
// jb -> ja
// ZPVac v0.62 007F2A18: // C3 DD D8 5D C3 55 8B EC
// fstp st(0) -> fstp st(6)
// Unlimited summon v0.62 004D6D95: //74 2D 8B 7C 24 0C 8B 07 6A 05 50 E8 ?? ?? ?? ??
// je -> jne
#pragma endregion

#pragma region CodeCave Addresses
/*ULONG levelHookAddr = 0x004E2B28; //Inside GW_CharacterStat::Decode()
ULONG levelHookDecode = 0x004E807A; //Start of _ZtrlSecureTear<unsigned char>
ULONG levelHookAddrRet = levelHookAddr + 7;
ULONG jobHookAddr = 0x004E2B3E; //Inside GW_CharacterStat::Decode()
ULONG jobHookDecode = 0x004E80EB; //Inside _ZtlSecureTear<short>
ULONG jobHookAddrRet = jobHookAddr + 7;*/
ULONG statHookAddr = 0x008D8581; //Inside CUIStatusBar::SetNumberValue
ULONG statHookAddrRet = statHookAddr + 5;
/*ULONG mesosHookAddr = 0x004E2D01; //Inside GW_CharacterStat::DecodeMoney()
ULONG mesosHookAddrRet = mesosHookAddr + 6;
ULONG mesosChangeHookAddr = 0x004E31FB; //Inside GW_CharacterStat::DecodeChangeStat()
ULONG mesosChangeHookAddrRet = mesosChangeHookAddr + 6;*/
ULONG mapNameHookAddr = 0x005CFA48; //Inside CItemInfo::GetMapString()
ULONG mapNameHookAddrRet = mapNameHookAddr + 6;
ULONG itemVacAddr = 0x005047AA; //Inside CDropPool::TryPickUpDrop()
ULONG itemVacAddrRet = itemVacAddr + 7;
ULONG mouseFlyXAddr = 0x009B62ED; //Inside CVecCtrl::raw__GetSnapshot()
ULONG mouseFlyXAddrRet = mouseFlyXAddr + 5;
ULONG mouseFlyYAddr = 0x009B6352; //Inside CVecCtrl::raw__GetSnapshot()
ULONG mouseFlyYAddrRet = mouseFlyYAddr + 5;
ULONG mobFreezeAddr = 0x009BCA92; //Inside CVecCtrlMob::WorkUpdateActive()
ULONG mobFreezeAddrRet = mobFreezeAddr + 6;
ULONG mobAutoAggroAddr = 0x009BCAF7; //Inside CVecCtrlMob::WorkUpdateActive() (call to CVecCtrl::WorkUpdateActive())
ULONG cVecCtrlWorkUpdateActiveCall = 0x009B19D0; //Start of CVecCtrl::WorkUpdateActive()
ULONG mobAutoAggroAddrRet = mobAutoAggroAddr + 5;
ULONG spawnPointAddr = 0x009B12A8; //Start of CVecCtrl::SetActive()
ULONG spawnPointAddrRet = spawnPointAddr + 5;
ULONG itemFilterAddr = 0x005059CC; //Inside CDropPool::OnDropEnterField()
ULONG itemFilterAddrRet = itemFilterAddr + 6;
ULONG mobFilter1Addr = 0x0067832D; //Inside CMobPool::SetLocalMob()
ULONG mobFilter1AddrRet = mobFilter1Addr + 5;
ULONG mobFilter1JmpAddr = 0x006783E2; //mov ecx,[ebp-0C] above the ret 0004 at the end of function
ULONG mobFilter2Addr = 0x0067948C; //Inside CMobPool::OnMobEnterField()
ULONG mobFilter2AddrRet = mobFilter2Addr + 5;
ULONG mobFilter2JmpAddr = 0x0067957F; //mov ecx,[ebp-0C] above the ret 0004 at the end of function
ULONG cInPacketDecode4Addr = 0x00406629; //Start of CInPacket::Decode4()
ULONG cOutPacketAddr = 0x0049637B;
ULONG cOutPacketAddrRet = cOutPacketAddr + 5;
#pragma endregion

#pragma region MapleStory Function Hook Addresses
// Addresses
ULONG enterCSAddr = 0x00A04DCA;
ULONG exitCSAddr = 0x0047C108;
ULONG ccAddr = 0x005304AF;
ULONG charLVLAddr = 0x004A8DE0; // TODO: Fix address
ULONG jobNameAddr = 0x004A77EF;
ULONG charDataAddr = 0x00425D0B;
// Hooks
typedef void(__stdcall *pfnCWvsContext__SendMigrateToShopRequest)(PVOID, PVOID, int); // Enters Cash Shop
auto CWvsContext__SendMigrateToShopRequest = reinterpret_cast<pfnCWvsContext__SendMigrateToShopRequest>(enterCSAddr);

typedef void(__stdcall *pfnCCashShop__SendTransferFieldPacket)(); // Exits Cash Shop
auto CCashShop__SendTransferFieldPacket = reinterpret_cast<pfnCCashShop__SendTransferFieldPacket>(exitCSAddr);

typedef int(__stdcall *pfnCField__SendTransferChannelRequest)(int nTargetChannel); // Changes Channel
auto CField__SendTransferChannelRequest = reinterpret_cast<pfnCField__SendTransferChannelRequest>(ccAddr);

typedef int(__stdcall *pfnCWvsContext__GetCharacterLevel)(ULONG, PVOID); // Retrieves Character Level
auto CWvsContext__GetCharacterLevel = reinterpret_cast<pfnCWvsContext__GetCharacterLevel>(charLVLAddr);

typedef char*(__cdecl *pfnGet_Job_Name)(int); // Retrieves Job name
auto GetJobName = reinterpret_cast<pfnGet_Job_Name>(jobNameAddr);

typedef void*(__thiscall *pfnCWvsContext__GetCharacterData)(ULONG, PVOID);
auto CWvsContext__GetCharacterData = reinterpret_cast<pfnCWvsContext__GetCharacterData>(charDataAddr);

//typedef ZXString<char>*(__fastcall* StringPool__GetString_t)(void *StringPool, void *edx, ZXString<char> *result, unsigned int nIdx);
//auto StringPool__GetString = (StringPool__GetString_t)0x0049B330; //
//void **ms_pInstance_StringPool = (void **)0x01C1C200; pointer that gets all Strings in StringPool
#pragma endregion

#pragma region Pointers Addresses & Offsets
ULONG PtInRectAddr = 0xBF0484;

#pragma region CLogin
ULONG LoginBase = 0xBEDED4; //CLogin
ULONG OFS_LoginStep = 0x168; //0 = login screen or logged in, 1 = Select World/Channel, 2 = Select Char
ULONG OFS_LoginScreen = 0x174; //255 == login screen, 1 == loggin in, 0 = logged in
#pragma endregion

#pragma region UIInfoBase
ULONG UIInfoBase = 0xBEC208; 
ULONG OFS_HP = 0xD18;
ULONG OFS_MP = OFS_HP + 4;
ULONG OFS_EXP = 0xBC8;
#pragma endregion

#pragma region CUIStatusBar
ULONG UIStatusBarBase = 0xBEBF9C; // CUIStatusBar
ULONG OFS_HPAlert = 0x80;
ULONG OFS_MPAlert = OFS_HPAlert + 4;
#pragma endregion

#pragma region CUIMiniMap
ULONG UIMiniMapBase = 0xBED788; // CUIMiniMap
ULONG p_CUiwndBase = 0x0;
ULONG m_nPaneW = 0x5B0;
ULONG m_nPaneH = 0x5B4;
ULONG m_nMini_W = 0x5B8;
ULONG m_nMini_H = 0x5BC;
ULONG m_nReal_W = 0x5C0;
ULONG m_nReal_H = 0x5C4;
ULONG m_nReal_CX = 0x5C8;
ULONG m_nReal_CY = 0x5CC;
//ULONG MiniMapCanvasPointer? = 0x5EC; -> OFS2 0x0 -> CanvasInterface
ULONG m_FootholdMap = 0x60C; // ZMap<long,ZRef<SimpleMiniMap_FootHold>,long>
//
//
//
// 00000C50 m_lFootHold   ???    ZArray<ZRef<SimpleMiniMap_FootHold>> ?
ULONG m_lLadderRope = 0x624; // ZList<ZRef<SimpleMiniMap_LadderRope>>
//
//
//
ULONG m_dwFieldID = 0x668;
ULONG m_dwSearchedShop = 0x66C;
ULONG m_bCreated = 0x670;
ULONG m_bShowMiniMap = 0x674;
#pragma endregion

#pragma region CWvsContext
ULONG ServerBase = 0x00BE7918; // CWvsContext 
ULONG OFS_World = 0x2054;
ULONG OFS_Channel = 0x2058;
ULONG OFS_CharacterCount = 0x20A0;
ULONG OFS_Tubi = 0x20A4;
ULONG OFS_CharacterData = 0x20B8; // CharacterStatBase*
ULONG OFS_PtrToCharData = OFS_CharacterData + 0x4; // ZRef<CharacterData>
#pragma endregion

#pragma region GW_CharacterStat
ULONG CharacterStatBase = 0xBF3CD8; //GW_CharacterStat //CWvsContext::GetCharacterData() returns ZRef<CharacterData>; &CharacterData[0] = GW_CharacterStat
ULONG OFS_CharID = 0x0; // uint
ULONG OFS_IGN = 0x4; // char[13]
ULONG OFS_Gender = 0x11; // short
ULONG OFS_Skin = 0x12; // short
ULONG OFS_Face = 0x13; // int
ULONG OFS_Hair = 0x17; // int 
ULONG OFS_PetLockerSN = 0x1B; // char[18] pet related, a serial number of pet locker ?
ULONG OFS_Level = 0x33; // ZtlSecurePack<short>
ULONG OFS_JobID = 0x39; // ZtlSecurePack<short>
ULONG OFS_CharStr = 0x41; // ZtlSecurePack<short>
ULONG OFS_CharDex = 0x49; // ZtlSecurePack<short>
ULONG OFS_CharInt = 0x51; // ZtlSecurePack<short>
ULONG OFS_CharLuk = 0x59; // ZtlSecurePack<short>
ULONG OFS_CharCurHP = 0x61; // ZtlSecurePack<short> // ZtlSecurePack<int> in 0.95
ULONG OFS_CharMaxHP = 0x69; // ZtlSecurePack<short>  // ZtlSecurePack<int> in 0.95
ULONG OFS_CharCurMP = 0x71; // ZtlSecurePack<short> // ZtlSecurePack<int> in 0.95
ULONG OFS_CharMaxMP= 0x79; // ZtlSecurePack<short> // ZtlSecurePack<int> in 0.95
ULONG OFS_CharAP = 0x81; // ZtlSecurePack<short>
ULONG OFS_CharSP = 0x89; // ZtlSecurePack<short>
ULONG OFS_CharCurXP = 0x91; // ZtlSecurePack<long> 
ULONG OFS_CharPOP = 0x9D; // ZtlSecurePack<short> popularity? just fame?
ULONG OFS_CharTempEXP = 0xB1; // ZtlSecurePack<long> nTempEXP??
ULONG OFS_Unknown5 = 0xD1; // ZtlSecurePack<uLong> dwPosMap
ULONG OFS_Mesos = 0xA5; // ZtlSecurePack<long>
#pragma endregion 

#pragma region CNpcPool
ULONG NpcPoolBase = 0xBED780; //CNpcPool

ULONG OFS_mNpc = 0x4; // m_mNpc, ZMap<unsigned long,__POSITION *,unsigned long>
ULONG OFS_mNpc_vfptr = OFS_mNpc + 0x0;			      // ZMap->_vfptr
ULONG OFS_mNpc_apTable = OFS_mNpc + 0x4;			  // ZMap->_m_apTable
ULONG OFS_mNpc_uTableSize = OFS_mNpc + 0x8;		      // ZMap->_m_uTableSize
ULONG OFS_mNpc_uCount = OFS_mNpc + 0xC;			      // ZMap->_m_uCount;
ULONG OFS_mNpc_uAutoGrowEvery128 = OFS_mNpc + 0x10;   // ZMap->_m_uAutoGrowEvery128;
ULONG OFS_mNpc_uAutoGrowLimit = OFS_mNpc + 0x14;	  // ZMap->_m_uAutoGrowLimit;
ULONG OFS_mNpc_end = OFS_mNpc + 0x18;				  // ZMap->ends 

ULONG OFS_lNpc = 0x1C; // m_lNpc, ZList<CNpcPool::NPCENTRY>
ULONG OFS_lNpc_vfptr = OFS_lNpc + 0x0;   // ZList->_vfptr
ULONG OFS_lNpc_gap4 = OFS_lNpc + 0x4;    // ZList->_gap4
ULONG OFS_lNpc_uCount = OFS_lNpc + 0x8;  // ZList->_m_uCount
ULONG OFS_lNpc_pHead = OFS_lNpc + 0xC;   // ZList->_m_pHead
ULONG OFS_lNpc_pTail = OFS_lNpc + 0x10;  // ZList->_m_pTail
ULONG OFS_lNpc_end = OFS_lNpc + 0x14;    // ZList->ends 

ULONG OFS_nTickCount = 0x30;  // (this->m_nTickCount + 1) % 33 run on void __thiscall CNpcPool::Update(CNpcPool *this)
ULONG OFS_wDay = 0x34; // relates to NPC timed update, void __thiscall CNpcPool::Update(CNpcPool *this)

ULONG OFS_mDisabledNpc = 0x38;  // ZMap<unsigned long, int, unsigned long>
ULONG OFS_mDisabledNpc_vfptr = OFS_mDisabledNpc + 0x0;			      // ZMap->_vfptr
ULONG OFS_mDisabledNpc_apTable = OFS_mDisabledNpc + 0x4;			  // ZMap->_m_apTable
ULONG OFS_mDisabledNpc_uTableSize = OFS_mDisabledNpc + 0x8;		      // ZMap->_m_uTableSize
ULONG OFS_mDisabledNpc_uCount = OFS_mDisabledNpc + 0xC;			      // ZMap->_m_uCount;
ULONG OFS_mDisabledNpc_uAutoGrowEvery128 = OFS_mDisabledNpc + 0x10;   // ZMap->_m_uAutoGrowEvery128;
ULONG OFS_mDisabledNpc_uAutoGrowLimit = OFS_mDisabledNpc + 0x14;	  // ZMap->_m_uAutoGrowLimit;
ULONG OFS_mDisabledNpc_end = OFS_mDisabledNpc + 0x18;				  // ZMap->ends 
#pragma endregion 

#pragma region CPortalList
ULONG PortalListBase = 0xBED768; // CPortalList 
ULONG OFS_PortalCount = 0x18;
#pragma endregion 

#pragma region CUserLocal
ULONG UserLocalBase = 0xBEBF98; // CUserLocal 
ULONG OFS_pID = 0x11A4;
ULONG OFS_Foothold = 0x1F0;
ULONG OFS_KB = 0x214;
ULONG OFS_KBX = 0x220;
ULONG OFS_KBY = 0x228;
ULONG OFS_Aggro = 0x250;
ULONG OFS_CharX = 0x3124;
ULONG OFS_CharY = OFS_CharX + 4;
ULONG OFS_AttackCount = 0x2B88;
ULONG OFS_Breath = 0x56C;
ULONG OFS_Morph = 0x528; //Change pointer to 9 and freeze
ULONG OFS_CharAnimation = 0x570;
ULONG OFS_Tele = 0x2B18;
ULONG OFS_TeleX = OFS_Tele + 8;
ULONG OFS_TeleY = OFS_TeleX + 4;
ULONG OFS_BuffCount = 0xBF4AD4; // Couldn't find it within CUserLocal, so static address
ULONG OFS_ComboCount = 0x3220;
#pragma endregion 

#pragma region CDropPool
ULONG DropPoolBase = 0xBED6AC; // CDropPool 
ULONG OFS_DropPoolBase_vfptr = 0x0;
ULONG OFS_tLastExplodeSound = 0x4;

ULONG OFS_mDrop = 0x8; // ZMap<unsigned long, ZRef<DROP>, unsigned long>
ULONG OFS_mDrop_vfptr = OFS_mDrop + 0x0;			  // ZMap->_vfptr
ULONG OFS_mDrop_apTable = OFS_mDrop + 0x4;			  // ZMap->_m_apTable
ULONG OFS_mDrop_uTableSize = OFS_mDrop + 0x8;		  // ZMap->_m_uTableSize
ULONG OFS_mDrop_uCount = OFS_mDrop + 0xC;			  // ZMap->_m_uCount;
ULONG OFS_mDrop_uAutoGrowEvery128 = OFS_mDrop + 0x10; // ZMap->_m_uAutoGrowEvery128;
ULONG OFS_mDrop_uAutoGrowLimit = OFS_mDrop + 0x14;	  // ZMap->_m_uAutoGrowLimit;
ULONG OFS_mDrop_end = OFS_mDrop + 0x18;				  // ZMap->ends 

ULONG OFS_lDrop = 0x20; // ZList<ZRef<DROP>>
ULONG OFS_lDrop_vfptr = OFS_lDrop + 0x0;   // ZList->_vfptr
ULONG OFS_lDrop_gap4 = OFS_lDrop + 0x4;    // ZList->_gap4
ULONG OFS_lDrop_uCount = OFS_lDrop + 0x8;  // ZList->_m_uCount
ULONG OFS_lDrop_pHead = OFS_lDrop + 0xC;   // ZList->_m_pHead
ULONG OFS_lDrop_pTail = OFS_lDrop + 0x10;  // ZList->_m_pTail
ULONG OFS_lDrop_end = OFS_lDrop + 0x14;    // ZList->ends 

ULONG OFS_mDropPoint = 0x34; // ZMap<unsigned long, tagPOINT, unsigned long>
ULONG OFS_mDropPoint_vfptr = OFS_mDropPoint + 0x0;			    // ZMap->_vfptr
ULONG OFS_mDropPoint_apTable = OFS_mDropPoint + 0x4;			// ZMap->_m_apTable
ULONG OFS_mDropPoint_uTableSize = OFS_mDropPoint + 0x8;		    // ZMap->_m_uTableSize
ULONG OFS_mDropPoint_uCount = OFS_mDropPoint + 0xC;			    // ZMap->_m_uCount;
ULONG OFS_mDropPoint_uAutoGrowEvery128 = OFS_mDropPoint + 0x10; // ZMap->_m_uAutoGrowEvery128;
ULONG OFS_mDropPoint_uAutoGrowLimit = OFS_mDropPoint + 0x14;	// ZMap->_m_uAutoGrowLimit;
ULONG OFS_mDropPoint_end = OFS_mDropPoint + 0x18;				// ZMap->ends 
ULONG OFS_pPropMoneyIcon = 0x4C; // _com_ptr_t<_com_IIID<IWzProperty, &_GUID_986515d9_0a0b_4929_8b4f_718682177b92>>
#pragma endregion 

#pragma region CWvsPhysicalSpace2D
ULONG CWvsPhysicalSpace2DBase = 0xBEBFA0; // CWvsPhysicalSpace2D 
ULONG OFS_CWvsPhysicalSpace2DBase_vfptr = 0x0;
ULONG OFS_constants = 0x4;  // ZRef<CONSTANTS>
ULONG OFS_icSwimArea = 0xC; // Geometry::InclusionChecker

ULONG OFS_rcMBR = 0x24; // tagRECT
ULONG OFS_rcMBR_left = OFS_rcMBR + 0x0;   // tagRECT->left
ULONG OFS_rcMBR_top = OFS_rcMBR + 0x4;    // tagRECT->top
ULONG OFS_rcMBR_right = OFS_rcMBR + 0x8;  // tagRECT->right
ULONG OFS_rcMBR_bottom = OFS_rcMBR + 0xC; // tagRECT->bottom
ULONG OFS_rcMBR_end = OFS_rcMBR + 0x10;   // tagRECT->ends

ULONG OFS_aMassRange = 0x34;  // ZArray<RANGE>
ULONG OFS_aIndexZMass = 0x34; // ZArray<long>
ULONG OFS_aaMassFootholdList = 0x3C; // ZArray<ZArray<unsigned long>>
#pragma endregion

#pragma region CUserPool
ULONG UserPoolBase = 0xBEBFA8; // CUserPool
ULONG OFS_baseclass_0 = 0x0;   // IGObj
ULONG OFS_pUserLocal = 0x4;    // ZRef<CUserLocal>

ULONG OFS_mUserRemote = 0xC;   // ZMap<unsigned long, ZRef<USERREMOTE_ENTRY>, unsigned long>
ULONG OFS_mUserRemote_apTable = 0x10;			// ZMap->_m_apTable
ULONG OFS_mUserRemote_uTableSize = 0x14;		// ZMap->_m_uTableSize
ULONG OFS_mUserRemote_uCount = 0x18;			// ZMap->_m_uCount; aka. OFS_PeopleCount;
ULONG OFS_mUserRemote_uAutoGrowEvery128 = 0x1C; // ZMap->_m_uAutoGrowEvery128;
ULONG OFS_mUserRemote_uAutoGrowLimit = 0x20;	// ZMap->_m_uAutoGrowLimit;

ULONG OFS_lUserRemote = 0x24; // ZList<ZRef<USERREMOTE_ENTRY>> 
ULONG OFS_lUserRemote_vfptr = OFS_lUserRemote + 0x0;   // ZList->_vfptr
ULONG OFS_lUserRemote_gap4 = OFS_lUserRemote + 0x4;    // ZList->_gap4
ULONG OFS_lUserRemote_uCount = OFS_lUserRemote + 0x8;  // ZList->_m_uCount
ULONG OFS_lUserRemote_pHead = OFS_lUserRemote + 0xC;   // ZList->_m_pHead
ULONG OFS_lUserRemote_pTail = OFS_lUserRemote + 0x10;  // ZList->_m_pTail
ULONG OFS_lUserRemote_end = OFS_lUserRemote + 0x14;    // ZList->ends 

ULONG OFS_lCouple = 0x38; // ZList<CUserPool::COUPLEENTRY>
ULONG OFS_lCouple_vfptr = OFS_lCouple + 0x0;   // ZList->_vfptr
ULONG OFS_lCouple_gap4 = OFS_lCouple + 0x4;    // ZList->_gap4
ULONG OFS_lCouple_uCount = OFS_lCouple + 0x8;  // ZList->_m_uCount
ULONG OFS_lCouple_pHead = OFS_lCouple + 0xC;   // ZList->_m_pHead
ULONG OFS_lCouple_pTail = OFS_lCouple + 0x10;  // ZList->_m_pTail
ULONG OFS_lCouple_end = OFS_lCouple + 0x14;    // ZList->ends 

ULONG OFS_tLoadEnd = 0x4C; // dd
ULONG OFS_tCooltimeEnd = 0x50; // dd

ULONG OFS_lDelayedLoad = 0x54; // ZList<ZRef<CUserRemote>>
ULONG OFS_lDelayedLoad_vfptr = OFS_lDelayedLoad + 0x0;   // ZList->_vfptr
ULONG OFS_lDelayedLoad_gap4 = OFS_lDelayedLoad + 0x4;    // ZList->_gap4
ULONG OFS_lDelayedLoad_uCount = OFS_lDelayedLoad + 0x8;  // ZList->_m_uCount
ULONG OFS_lDelayedLoad_pHead = OFS_lDelayedLoad + 0xC;   // ZList->_m_pHead
ULONG OFS_lDelayedLoad_pTail = OFS_lDelayedLoad + 0x10;  // ZList->_m_pTail
ULONG OFS_lDelayedLoad_end = OFS_lDelayedLoad + 0x14;    // ZList->ends 

ULONG OFS_lFriend = 0x68; // ZList<CUserPool::FRIENDENTRY>
ULONG OFS_lFriend_vfptr = OFS_lFriend + 0x0;   // ZList->_vfptr
ULONG OFS_lFriend_gap4 = OFS_lFriend + 0x4;    // ZList->_gap4
ULONG OFS_lFriend_uCount = OFS_lFriend + 0x8;  // ZList->_m_uCount
ULONG OFS_lFriend_pHead = OFS_lFriend + 0xC;   // ZList->_m_pHead
ULONG OFS_lFriend_pTail = OFS_lFriend + 0x10;  // ZList->_m_pTail
ULONG OFS_lFriend_end = OFS_lFriend + 0x14;    // ZList->ends 

//0000007C m_lNewYearCard  ZList<CUserPool::NEWYEARCARDENTRY> ?
//00000090 m_lAllNewYearCardEntry ZMap<unsigned long, ZList<unsigned long>, unsigned long> ?
//000000A8 m_lMarriage     ZList<CUserPool::MARRIAGEENTRY> ?
//000000BC m_lCoupleChair  ZList<CUserPool::COUPLECHAIRENTRY> ?
//000000D0 CUserPool       ends
#pragma endregion 

#pragma region CInputSystem
ULONG InputBase = 0xBEC33C; // CInputSystem
ULONG OFS_MouseAnimation = 0x9B4;
ULONG OFS_MouseLocation = 0x978;
ULONG OFS_MouseX = 0x8C;
ULONG OFS_MouseY = OFS_MouseX + 4;
#pragma endregion 

#pragma region CMobPool
ULONG MobPoolBase = 0xBEBFA4; // CMobPool
ULONG OFS_MobPoolBase_vfptr = 0x0;

ULONG OFS_mMob = 0x4; // ZMap<unsigned long, __POSITION *, unsigned long>
ULONG OFS_mMob_apTable = OFS_mMob + 0x4;			// ZMap->_m_apTable
ULONG OFS_mMob_uTableSize = OFS_mMob + 0x8;			// ZMap->_m_uTableSize
ULONG OFS_mMob_uCount = OFS_mMob + 0xC;		 		// ZMap->_m_uCount;
ULONG OFS_mMob_uAutoGrowEvery128 = OFS_mMob + 0x10; // ZMap->_m_uAutoGrowEvery128;
ULONG OFS_mMob_uAutoGrowLimit = OFS_mMob + 0x14;	// ZMap->_m_uAutoGrowLimit;
ULONG OFS_mMob_end = OFS_mMob + 0x18;				// ZMap->ends 

ULONG OFS_lMob = 0x1C; // ZList<ZRef<CMob>>
ULONG OFS_lMob_vfptr = OFS_lMob + 0x0;   // ZList->_vfptr
ULONG OFS_lMob_gap4 = OFS_lMob + 0x4;    // ZList->_gap4
ULONG OFS_lMob_uCount = OFS_lMob + 0x8;  // ZList->_m_uCount, aka. OFS_MobCount = 0x24;
ULONG OFS_lMob_pHead = OFS_lMob + 0xC;   // ZList->_m_pHead
ULONG OFS_lMob_pTail = OFS_lMob + 0x10;  // ZList->_m_pTail
ULONG OFS_lMob_end = OFS_lMob + 0x14;    // ZList->ends 

ULONG OFS_lMobDelayedDead = 0x30; // ZList<ZRef<CMob>>
ULONG OFS_lMobDelayedDead_vfptr = OFS_lMobDelayedDead + 0x0;   // ZList->_vfptr
ULONG OFS_lMobDelayedDead_gap4 = OFS_lMobDelayedDead + 0x4;    // ZList->_gap4
ULONG OFS_lMobDelayedDead_uCount = OFS_lMobDelayedDead + 0x8;  // ZList->_m_uCount
ULONG OFS_lMobDelayedDead_pHead = OFS_lMobDelayedDead + 0xC;   // ZList->_m_pHead
ULONG OFS_lMobDelayedDead_pTail = OFS_lMobDelayedDead + 0x10;  // ZList->_m_pTail
ULONG OFS_lMobDelayedDead_end = OFS_lMobDelayedDead + 0x14;    // ZList->ends 

ULONG OFS_lMobDeadProcess = 0x44; // ZList<ZRef<CMob>>
ULONG OFS_lMobDeadProcess_vfptr = OFS_lMobDeadProcess + 0x0;   // ZList->_vfptr
ULONG OFS_lMobDeadProcess_gap4 = OFS_lMobDeadProcess + 0x4;    // ZList->_gap4
ULONG OFS_lMobDeadProcess_uCount = OFS_lMobDeadProcess + 0x8;  // ZList->_m_uCount
ULONG OFS_lMobDeadProcess_pHead = OFS_lMobDeadProcess + 0xC;   // ZList->_m_pHead
ULONG OFS_lMobDeadProcess_pTail = OFS_lMobDeadProcess + 0x10;  // ZList->_m_pTail
ULONG OFS_lMobDeadProcess_end = OFS_lMobDeadProcess + 0x14;    // ZList->ends 

ULONG OFS_pMobDamagedByMob = 0x58; // ZRef<CMob>
ULONG OFS_tLastHitMobDamagedByMob = 0x60; // dd
ULONG OFS_pGuidedMob = 0x64; // ZRef<CMob>
ULONG OFS_dwMobCrcKey = 0x6C; // dd
ULONG OFS_CMobPool_end = 0x70; // ends   

//TODO: delete or refactor
ULONG OFS_Mob1 = 0x28;
ULONG OFS_Mob2 = 0x4;
ULONG OFS_Mob3 = 0x120;
ULONG OFS_Mob4 = 0x24;
ULONG OFS_MobX = 0x60;
ULONG OFS_MobY = OFS_MobX + 4;
ULONG OFS_DeadMob = 0x7C; //Wrong
#pragma endregion 

#pragma region CItemInfo
ULONG CItemInfo = 0xBE78D8;
#pragma endregion 

#pragma region StringPool
ULONG StringPool = 0xBF0D0C;
ULONG StringPool_apZMString = 0x0; // ZArray<ZXString<char>*> 
ULONG StringPool_apZWString = 0x4; // ZArray<ZXString<unsigned short>*>
ULONG StringPool_m_lock = 0x8; // ZFatalSection
ULONG StringPool_end = 0x10; // ends 
#pragma endregion 

#pragma endregion