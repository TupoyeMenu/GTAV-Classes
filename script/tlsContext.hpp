#pragma once
#include "../rage/sysMemAllocator.hpp"
#include "scrThread.hpp"

#if _WIN32
#include <intrin.h>
#endif

namespace rage
{
	class tlsContext
	{
	public:
		rage::sysMemAllocator* getAllocator()
		{
			return *(::rage::sysMemAllocator**)((intptr_t)this + offsets::tls_context_allocator_offset);
		}
		rage::sysMemAllocator** getAllocatorPtr()
		{
			return (::rage::sysMemAllocator**)((intptr_t)this + offsets::tls_context_allocator_offset);
		}
		void** getScriptThreadPtr()
		{
			return (void**)((intptr_t)this + offsets::tls_context_thread_offset);
		}
		bool* getScriptThreadActivePtr()
		{
			return (bool*)((intptr_t)this + offsets::tls_context_thread_offset + sizeof(void*));
		}

		static tlsContext* get()
		{
			constexpr std::uint32_t TlsIndex = 0x0;
			return *reinterpret_cast<tlsContext**>(__readgsqword(0x58) + TlsIndex);
		}
	};
}