#pragma once
namespace detours {
	bool redirect(bool enable, void** function, void* redirection);
}