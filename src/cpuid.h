#ifndef __H_CPUID_NODE_H__
#define __H_CPUID_NODE_H__

#if defined(_MSC_VER)
#	pragma warning(disable : 4506 4800)
#endif

namespace cpuid {
	class CPUID {
	public:
		static void Initialize(v8::Handle<v8::Object> target);
	};
}

#endif
