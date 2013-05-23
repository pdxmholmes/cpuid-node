#ifndef __H_CPUID_NODE_H__
#define __H_CPUID_NODE_H__

namespace cpuid {
	class CPUID {
	public:
		static void Initialize(v8::Handle<v8::Object> target);
	};
}

#endif
