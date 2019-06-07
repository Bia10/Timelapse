/*
#include "Macro.h"

MacroEntry::MacroEntry() {
	bw = gcnew System::ComponentModel::BackgroundWorker;
	bw->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &MacroEntry::CastBackground);
	timer = gcnew Windows::Forms::Timer;
	timer->Tick += gcnew EventHandler(this, &MacroEntry::MacroTick);
}

MacroEntry::MacroEntry(String^ name, int interval, int key) {
	Name = name;
	Delay = interval;
	KeyCode = key;

	bw = gcnew System::ComponentModel::BackgroundWorker;
	bw->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &MacroEntry::CastBackground);
	timer = gcnew Windows::Forms::Timer;
	timer->Tick += gcnew EventHandler(this, &MacroEntry::MacroTick);
}

MacroEntry::~MacroEntry() {
	delete timer;
	delete bw;
}

Void MacroEntry::MacroTick(Object^  sender, EventArgs^  e) {
	Cast();
}

Void MacroEntry::Cast() {
	if (!bw->IsBusy)
		bw->RunWorkerAsync();
}

Void MacroEntry::CastBackground(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^  e)
{
	if (!HelperFuncs::IsInGame()) return;
	// TODO: other kinds of checks before casting macro
	// CCing,entering/exiting CS, Trading, Playing games, Using Slow cast Macros

	//Send Key
	while (AutoSkill::UsingAutoSkill) Sleep(100);
	AutoSkill::UsingAutoSkill = true;
	Sleep(100);
	//CMS::SendSwitch(keyIndex);
	Sleep(100);
	AutoSkill::UsingAutoSkill = false;
}*/

/*
using namespace System;
using namespace IO;
using namespace Collections::Generic;
using namespace Xml::Serialization;
public ref class MacroEntry {
public:
	// CTOR
	MacroEntry();
	// CTOR
	MacroEntry(String^ name, int interval, int key);
	// DTOR
	~MacroEntry();
	// Action call
	void Cast();

	String^ Name;
	int KeyCode;
	property int Delay
	{
		int get()
		{
			return timer->Interval / 1000;
		}
		void set(int i)
		{
			timer->Interval = i * 1000;
		}
	}
	[System::Xml::Serialization::XmlIgnoreAttribute]
	property bool Enabled
	{
		void set(bool state)
		{
			if (state) Cast();
			timer->Enabled = state;
		}
		bool get()
		{
			return timer->Enabled;
		}
	}

private:
	Windows::Forms::Timer^ timer;
	void MacroTick(Object^  sender, EventArgs^  e);

	System::ComponentModel::BackgroundWorker^ bw;
	void CastBackground(Object^ sender, System::ComponentModel::DoWorkEventArgs^  e);
};

public ref class AutoSkill {
public:
	static List<MacroEntry^>^ AutoSkills = gcnew List<MacroEntry^>;
	static bool UsingAutoSkill;
}; */