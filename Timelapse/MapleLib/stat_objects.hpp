#pragma once
#include <winnt.h>
#include "native.hpp"
#include "ZtlSecure.hpp"
#include "../detours.hpp"
#include "../MapleFunctions.h"

namespace Timelapse {
#pragma pack(push, 1)
class GW_CharacterStat {	
	~GW_CharacterStat() = delete;
public:
	short get_Lvl() {
		try { return this->nLevel.Fuse(); }
		catch (std::exception& e) { UNREFERENCED_PARAMETER(e); }
		return 0;
	}
	static short get_Lvl(GW_CharacterStat *charStat) {
		try { return charStat->nLevel.Fuse(); }
		catch (std::exception& e) { UNREFERENCED_PARAMETER(e); }
		return 0;
	}
	short get_Job() {
		try { return this->nJob.Fuse(); }
		catch (std::exception& e) { UNREFERENCED_PARAMETER(e); }
		return 0;
	}
	short get_STR() {
		try { return this->nSTR.Fuse(); }
		catch (std::exception& e) { UNREFERENCED_PARAMETER(e); }
		return 0;
	}
	short get_DEX() {
		try { return this->nDEX.Fuse(); }
		catch (std::exception& e) { UNREFERENCED_PARAMETER(e); }
		return 0;
	}
	short get_INT() {
		try { return this->nINT.Fuse(); }
		catch (std::exception& e) { UNREFERENCED_PARAMETER(e); }
		return 0;
	}
	short get_LUK() {
		try { return this->nLUK.Fuse(); }
		catch (std::exception& e) { UNREFERENCED_PARAMETER(e); }
		return 0;
	}
	short get_HP() {
		Log::WriteLineToConsole("FUSING HP");
		try { return this->nHP.Fuse(); }
		catch (std::exception& e) { UNREFERENCED_PARAMETER(e); }
		return 0;
	}
	short get_MP() {
		Log::WriteLine("FUSING MP");
		const SHORT charMP = readShortValueZtlSecureFuse(*reinterpret_cast<ULONG*>(CharacterStatBase) + OFS_CharCurMP);
		return charMP;

		/*try { return this->nMP.Fuse(); }
		catch (std::exception& ex) {
			Log::WriteLine("ERROR WHILE FUSING MP!!");
			throw std::exception(ex);
			UNREFERENCED_PARAMETER(ex);
		}
		return 0;*/
	}
	short get_AP() {
		try { return this->nAP.Fuse(); }
		catch (std::exception& e) { UNREFERENCED_PARAMETER(e); }
		return 0;
	}

private:
	unsigned int dwCharacterID = 0;			// 0x00
	char sCharacterName[13] = {};			// 0x04
	char nGender = 0;						// 0x11
	char nSkin = 0;							// 0x12
	int  nFace = 0;							// 0x13
	int  nHair = 0;							// 0x17
	char petLockerSn[18] = {};				// 0x1B
	ZtlSecurePack<short> nLevel;			// 0x33
	ZtlSecurePack<short> nJob;				// 0x39
	ZtlSecurePack<short> nSTR;				// 0x41
	ZtlSecurePack<short> nDEX;				// 0x49
	ZtlSecurePack<short> nINT;				// 0x51
	ZtlSecurePack<short> nLUK;				// 0x59
	ZtlSecurePack<short> nHP;				// 0x61
	ZtlSecurePack<short> nMHP;				// 0x69
	ZtlSecurePack<short> nMP;				// 0x71 113
	ZtlSecurePack<short> nMMP;				// 0x79 121
	ZtlSecurePack<short> nAP;				// 0x81 129
	ZtlSecurePack<short> nSP;				// 0x89 137
	ZtlSecurePack<long>  nCurXP;			// 0x91 145
	ZtlSecurePack<short> nPOP;				// 0x9D 157
	ZtlSecurePack<long>  nMoney;			// 0xA5 165
	ZtlSecurePack<long>  nTempXP;			// 0xB1 177
	int extendSP;							// 0xBD 189 ExtendSP::Decode 
											// 0xC9 201 ?????
								            // 0xCD 205 ?????
	//ZtlSecurePack<uLong> dwPosMap;        // 0xD1 209
	//long nCheckSum;                       // 0xDA 218
	char nPortal;						    // 0xDD 221
	//char nItemCountCheckSum;				// 0xE2 226
	int  nPlaytime;							// 0xE3 227
	//short nSubJob;						// 0xE7 231
	// GW_CharacterStat ends                // 0xE9 233
	};
#pragma pack(pop)

/*class CharacterData {
	~CharacterData() = delete;
public:
	GW_CharacterStat characterStat;
};

struct BasicStat {
	~BasicStat() = delete;
private:
	ZtlSecure<int> nGender;					// 0x00
	ZtlSecure<int> nLevel;					// 0x0C
	ZtlSecure<int> nJob;					// 0x18
	ZtlSecure<int> nSTR;					// 0x24
	ZtlSecure<int> nDEX;					// 0x30
	ZtlSecure<int> nINT;					// 0x3C
	ZtlSecure<int> nLUK;					// 0x48
	ZtlSecure<int> nPOP;					// 0x54
	ZtlSecure<int> nMHP;					// 0x60 
	ZtlSecure<int> nMHPOfItem;				// 0x6C
	ZtlSecure<int> nMMP;					// 0x78
	ZtlSecure<int> nPvPDamage;				// 0x84
	ZtlSecure<char> nCharisma;				//  
	ZtlSecure<char> nInsight;				// 
	ZtlSecure<char> nWill;					// 
	ZtlSecure<char> nCraft;					// 
	ZtlSecure<char> nSense;					// 
	ZtlSecure<char> nCharm;					// 
	ZtlSecure<int> bPvP;					// 
	ZtlSecure<int> nAttackCountIncByEquip;	// 
	ZMap<unsigned long, long, unsigned long> m_mSetItemMobDamR;
public:
	int get_max_hp() {
		try {
			return this->nMHP.Fuse();
		}
		catch (std::exception& e) {
			UNREFERENCED_PARAMETER(e);
		}
		return 0;
	}
	int get_max_mp() {
		try {
			return this->nMMP.Fuse();
		}
		catch (std::exception& e) {
			UNREFERENCED_PARAMETER(e);
		}
		return 0;
	}	
};

class CUIStat : public CWnd, public TSingleton<CUIStat, TSingleton_CUIStat> {
	~CUIStat() = delete;
public:
	void click_button(unsigned char id) {
		unsigned int auto_ap_up_button_ids[] = {
			2010,		// Regular
			2011,		// Pirate (Brawler)
			2012,		// Pirate (Gunslinger)
			2013,		// Xenon (STR)
			2014,		// Xenon (DEX)
			2015		// Xenon (LUK)
		};

		if (id >= 0 && id < _countof(auto_ap_up_button_ids))
			return this->OnButtonClicked(auto_ap_up_button_ids[id]);
	}
};*/

//(sizeof(GW_CharacterStat), 0x86);
//static_assert_size(sizeof(BasicStat), 0xF0);

const unsigned int GW_CharacterStat__DecodeChangeStat_address = 0x004E2FBA; // TODO: get AOB or way to find it
typedef int(__stdcall* GW_CharacterStat__DecodeChangeStat_t)(GW_CharacterStat *ecx, void* edx, CInPacket *iPacket);
static GW_CharacterStat__DecodeChangeStat_t GW_CharacterStat__DecodeChangeStat = reinterpret_cast<GW_CharacterStat__DecodeChangeStat_t>(GW_CharacterStat__DecodeChangeStat_address);

	inline bool Hook_GW_CharacterStat__DecodeChangeStat(bool enable) {
		const GW_CharacterStat__DecodeChangeStat_t GW_CharacterStat__DecodeChangeStat_hook = [](GW_CharacterStat *ecx, void *edx, CInPacket *iPacket) -> int {
			int flags = GW_CharacterStat__DecodeChangeStat(ecx, edx, iPacket);
			Log::WriteLineToConsole("HOOK: after call: FLAGS: " + flags.ToString());

				 const int gender_flag = 0x1;
				 const int skin_flag = 0x2;
				 const int face_flag = 0x4;
				 const int hair_flag = 0x8;
				 const int lvl_flag = 0x10;
				 const int job_flag = 0x20;
				 const int str_flag = 0x40;
				 const int dex_flag = 0x80;
				 const int int_flag = 0x100;
				 const int luk_flag = 0x200;
				 const int hp_flag = 0x400;
				 const int max_hp_flag = 0x800;
				 const int mp_flag = 0x1000;
				 const int max_mp_flag = 0x2000;
				 const int ap_flag = 0x4000;
				 const int sp_flag = 0x8000;
				 const int EXP_flag = 0x10000;
				 const int POP_flag = 0x20000;
				 const int money_flag = 0x40000;
				 const int aliPetLockerSN1_flag = 0x80000;  //aliPetLockerSN[1]
				 const int aliPetLockerSN2_flag = 0x100000; //aliPetLockerSN[2]
				 const int tempEXP_flag = 0x200000;

			if (flags) 
			{
				switch (flags) 
				{
				/*case gender_flag: 
					Log::WriteLineToConsole("HOOK: " + flags.ToString() + " returned!");
					break;
				case skin_flag: 
					Log::WriteLineToConsole("HOOK: " + flags.ToString() + " returned!");
					break;
				case face_flag:  
					Log::WriteLineToConsole("HOOK: " + flags.ToString() + " returned!"); 
					break;
				case hair_flag:  
					Log::WriteLineToConsole("HOOK: " + flags.ToString() + " returned!"); 
					break;
				case lvl_flag:
					Log::WriteLineToConsole("HOOK: " + flags.ToString() + " returned!");
					break;
				case job_flag:  
					Log::WriteLineToConsole("HOOK: " + flags.ToString() + " returned!"); 
					break;
				case str_flag:  
					Log::WriteLineToConsole("HOOK: " + flags.ToString() + " returned!"); 
					break;
				case dex_flag:  
					Log::WriteLineToConsole("HOOK: " + flags.ToString() + " returned!"); 
					break;
				case int_flag:  
					Log::WriteLineToConsole("HOOK: " + flags.ToString() + " returned!"); 
					break;
				case luk_flag:  
					Log::WriteLineToConsole("HOOK: " + flags.ToString() + " returned!"); 
					break;
				case hp_flag:  
					Log::WriteLineToConsole("HOOK: " + flags.ToString() + " returned!"); 
					break;
				case max_hp_flag:  
					Log::WriteLineToConsole("HOOK: " + flags.ToString() + " returned!"); 
					break;
				case mp_flag:  
					Log::WriteLineToConsole("HOOK: " + flags.ToString() + " returned!"); 
					break;
				case max_mp_flag: 
					Log::WriteLineToConsole("HOOK: " + flags.ToString() + " returned!"); 
					break;
				case ap_flag:  
					Log::WriteLineToConsole("HOOK: " + flags.ToString() + " returned!"); 
					break;
				case sp_flag:  
					Log::WriteLineToConsole("HOOK: " + flags.ToString() + " returned!");
					break;
				case EXP_flag:  
					Log::WriteLineToConsole("HOOK: " + flags.ToString() + " returned!"); 
					break;
				case POP_flag:  
					Log::WriteLineToConsole("HOOK: " + flags.ToString() + " returned!"); 
					break;*/
				default:  
					Log::WriteLineToConsole("HOOK: unhandled flag" + flags.ToString() + " returned!");;
				}
			}

		return flags;
		};

	Log::WriteLine("HOOK: before Detour attached");
	return detours::redirect(enable, reinterpret_cast<void**>(&GW_CharacterStat__DecodeChangeStat), GW_CharacterStat__DecodeChangeStat_hook);
	}
}
