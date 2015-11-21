#include <sstream>
#include "WinUtils.hpp"

namespace {
#if _M_IX86
	/**
	*  Callback buffer to convert __stdcall to 
	* __thiscall. Assembly version is something 
	* like:
	*
	* _callback_blob_start:
	*	push ebp
	*	mov ebp, esp
	*	pushad
	*	jmp .end
	*.bounce:
	*	pop esi
	*	lodsd
	*	mov ecx, eax
	*	lodsd
	*	mov edx, [ebp + 0x14]
	*	push edx
	*	mov edx, [ebp + 0x10]
	*	push edx
	*	mov edx, [ebp + 0x0c]
	*	push edx
	*	mov edx, [ebp + 0x08]
	*	push edx
	*	call eax
	*	mov [ebp - 0x04], eax
	*	popad
	*	pop ebp
	*	ret 0x10
	*.end:
	*	call .bounce
	*/
	std::array<unsigned char, 42> callback_buf = {
		0x55, 0x89, 0xe5, 0x60, 0xeb, 0x1f,
		0x5e, 0xad, 0x89, 0xc1, 0xad, 0x8b, 
		0x55, 0x14, 0x52, 0x8b, 0x55, 0x10, 
		0x52, 0x8b, 0x55, 0x0c, 0x52, 0x8b, 
		0x55, 0x08, 0x52, 0xff, 0xd0, 0x89,
		0x45, 0xfc, 0x61, 0x5d, 0xc2, 0x10, 
		0x00, 0xe8, 0xdc, 0xff, 0xff, 0xff,
	};


#pragma pack(push, 1)
	struct CallbackBlob {
		std::array<unsigned char, 42> innerBytes_;
		size_t thisPtr_;
		size_t funcPtr_;
	};
#pragma pack(pop)

	std::pair<std::shared_ptr<void>, size_t> makeWindowsCallback(size_t thisptr, size_t fptr)
	{
		
		CallbackBlob blob;

		std::copy(callback_buf.begin(), callback_buf.end(), blob.innerBytes_.begin());
		blob.funcPtr_ = fptr;
		blob.thisPtr_ = thisptr;

		auto tmp = VirtualAlloc(nullptr, sizeof(blob), MEM_COMMIT, PAGE_READWRITE);
		if (nullptr == tmp)
			throw std::bad_alloc();

		memcpy(tmp, &blob, sizeof(blob));

		return std::make_pair(std::shared_ptr<void>(tmp, [](void* p) { VirtualFree(p, 0, MEM_RELEASE); }), sizeof(blob));
	}

#else if _M_X64


#endif
}


namespace entomoid {
	namespace utils {

		std::shared_ptr<void> windows_getCallback(size_t thisptr, void* fptr)
		{
			DWORD oldProtect = 0;
			size_t bufSize = 0;
			std::shared_ptr<void> ptr;

			std::tie(ptr, bufSize) = makeWindowsCallback(thisptr, reinterpret_cast<size_t>(fptr));

			if (!VirtualProtect(ptr.get(), bufSize, PAGE_EXECUTE_READ, &oldProtect)) {
				WRAP_WINDOWS_RUNTIME_ERROR("Unable to set callback buffer to executable!");
			}
			
			return ptr;

		}
	}

}