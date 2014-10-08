#include <node.h>
#include <nan.h>
#include <v8.h>
#include <libcpuid.h>
#include "cpuid.h"

namespace cpuid {
	using namespace v8;

	static const char* mapVendor(cpu_vendor_t vendor) {
		switch(vendor) {
			case VENDOR_INTEL:
				return "intel";

			case VENDOR_AMD:
				return "amd";

			case VENDOR_CYRIX:
				return "cyrix";

			case VENDOR_NEXGEN:
				return "nexgen";

			case VENDOR_TRANSMETA:
				return "transmeta";

			case VENDOR_UMC:
				return "umc";

			case VENDOR_CENTAUR:
				return "idt";

			case VENDOR_RISE:
				return "rise";

			case VENDOR_SIS:
				return "sis";

			case VENDOR_NSC:
				return "nsc";

			default:
				return "unknown";
		}
	}

	static void fillFeatures(Handle<Object> features, cpu_id_t& cpuData) {
		features->Set(NanNew<String>("fpu"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_FPU]));
		features->Set(NanNew<String>("virtualModeExtension"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_VME]));
		features->Set(NanNew<String>("debuggingExtension"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_DE]));
		features->Set(NanNew<String>("pageSizeExtension"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_PSE]));
		features->Set(NanNew<String>("timeStampCounter"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_TSC]));
		features->Set(NanNew<String>("modelSpecificRegisters"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_MSR]));
		features->Set(NanNew<String>("physicalAddressExtension"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_PAE]));
		features->Set(NanNew<String>("machineCheckException"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_MCE]));
		features->Set(NanNew<String>("cx8Instruction"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_CX8]));
		features->Set(NanNew<String>("apic"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_APIC]));
		features->Set(NanNew<String>("mtrr"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_MTRR]));
		features->Set(NanNew<String>("sepInstructions"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_SEP]));
		features->Set(NanNew<String>("pageGlobalEnable"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_PGE]));
		features->Set(NanNew<String>("machineCheckArchitecture"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_MCA]));
		features->Set(NanNew<String>("cmovInstructions"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_CMOV]));
		features->Set(NanNew<String>("pageAttributeTable"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_PAT]));
		features->Set(NanNew<String>("pageAddressExtension36bit"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_PSE36]));
		features->Set(NanNew<String>("processorSerialNumber"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_PN]));
		features->Set(NanNew<String>("clflushInstruction"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_CLFLUSH]));
		features->Set(NanNew<String>("debugStore"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_DTS]));
		features->Set(NanNew<String>("acpi"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_ACPI]));
		features->Set(NanNew<String>("mmx"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_MMX]));
		features->Set(NanNew<String>("fxsrInstructions"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_FXSR]));
		features->Set(NanNew<String>("sse"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_SSE]));
		features->Set(NanNew<String>("sse2"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_SSE2]));
		features->Set(NanNew<String>("selfSnoop"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_SS]));
		features->Set(NanNew<String>("hyperthreading"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_HT]));
		features->Set(NanNew<String>("thermalMonitor"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_TM]));
		features->Set(NanNew<String>("ia64"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_IA64]));
		features->Set(NanNew<String>("pendingBreakEnable"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_PBE]));
		features->Set(NanNew<String>("sse3"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_PNI]));
		features->Set(NanNew<String>("pclmulInstruction"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_PCLMUL]));
		features->Set(NanNew<String>("debugStore64bit"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_DTS64]));
		features->Set(NanNew<String>("monitor"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_MONITOR]));
		features->Set(NanNew<String>("cplDebugStore"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_DS_CPL]));
		features->Set(NanNew<String>("virtualization"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_VMX]));
		features->Set(NanNew<String>("saferModeException"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_SMX]));
		features->Set(NanNew<String>("enhancedSpeedStep"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_EST]));
		features->Set(NanNew<String>("thermalMonitor2"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_TM2]));
		features->Set(NanNew<String>("ssse3Instructions"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_SSSE3]));
		features->Set(NanNew<String>("contextId"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_CID]));
		features->Set(NanNew<String>("cx16Instruction"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_CX16]));
		features->Set(NanNew<String>("tprDisable"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_XTPR]));
		features->Set(NanNew<String>("stpmDisable"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_XTPR]));
		features->Set(NanNew<String>("pdcm"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_PDCM]));
		features->Set(NanNew<String>("directCacheAccess"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_DCA]));
		features->Set(NanNew<String>("sse41"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_SSE4_1]));
		features->Set(NanNew<String>("sse42"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_SSE4_2]));
		features->Set(NanNew<String>("syscallInstructions"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_SYSCALL]));
		features->Set(NanNew<String>("executeDisableBit"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_XD]));
		features->Set(NanNew<String>("movbeInstruction"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_MOVBE]));
		features->Set(NanNew<String>("popcntInstruction"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_POPCNT]));
		features->Set(NanNew<String>("aesInstructions"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_AES]));
		features->Set(NanNew<String>("xsaveInstructions"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_XSAVE]));
		features->Set(NanNew<String>("osxsaveInstruction"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_OSXSAVE]));
		features->Set(NanNew<String>("avx"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_AVX]));
		features->Set(NanNew<String>("mmxExt"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_MMXEXT]));
		features->Set(NanNew<String>("amd3dNow"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_3DNOW]));
		features->Set(NanNew<String>("amd3dNowExt"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_3DNOWEXT]));
		features->Set(NanNew<String>("noExecuteBit"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_NX]));
		features->Set(NanNew<String>("fxsrOptimizations"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_FXSR_OPT]));
		features->Set(NanNew<String>("rdtscpInstruction"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_RDTSCP]));
		features->Set(NanNew<String>("em64t"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_LM]));
		features->Set(NanNew<String>("x86_64"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_LM]));
		features->Set(NanNew<String>("lahf64bit"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_LAHF_LM]));
		features->Set(NanNew<String>("cmpLegacy"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_CMP_LEGACY]));
		features->Set(NanNew<String>("secureVirtualMachine"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_SVM]));
		features->Set(NanNew<String>("lzcntInstruction"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_ABM]));
		features->Set(NanNew<String>("misalignedSSE"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_MISALIGNSSE]));
		features->Set(NanNew<String>("sse4a"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_SSE4A]));		
		features->Set(NanNew<String>("amd3dNowPrefetch"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_3DNOWPREFETCH]));
		features->Set(NanNew<String>("osVisibleWorkaround"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_OSVW]));
		features->Set(NanNew<String>("instructionBasedSampling"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_IBS]));
		features->Set(NanNew<String>("sse5"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_SSE5]));
		features->Set(NanNew<String>("skinitInstructions"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_SKINIT]));
		features->Set(NanNew<String>("watchdogTimer"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_WDT]));
		features->Set(NanNew<String>("temperatureSensor"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_TS]));
		features->Set(NanNew<String>("frequencyIDControl"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_FID]));
		features->Set(NanNew<String>("voltageIDControl"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_VID]));
		features->Set(NanNew<String>("thermtrip"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_TTP]));
		features->Set(NanNew<String>("amdThermalControl"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_TM_AMD]));
		features->Set(NanNew<String>("softwareThermalControl"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_STC]));
		features->Set(NanNew<String>("multiplierSteps100mhz"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_100MHZSTEPS]));
		features->Set(NanNew<String>("hardwarePState"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_HWPSTATE]));
		features->Set(NanNew<String>("constantTSCTicks"), NanNew<Boolean>(cpuData.flags[CPU_FEATURE_CONSTANT_TSC]));
	}

	static void fillCache(Handle<Object> cache, cpu_id_t& cpuData) {
		Local<Object> l1 = NanNew<Object>();
		cache->Set(NanNew<String>("l1"), l1);

		l1->Set(NanNew<String>("data"), NanNew<Integer>(cpuData.l1_data_cache));
		l1->Set(NanNew<String>("instruction"), NanNew<Integer>(cpuData.l1_instruction_cache));
		l1->Set(NanNew<String>("associativity"), NanNew<Integer>(cpuData.l1_assoc));
		l1->Set(NanNew<String>("cacheline"), NanNew<Integer>(cpuData.l1_cacheline));

		Local<Object> l2 = NanNew<Object>();
		cache->Set(NanNew<String>("l2"), l2);

		l2->Set(NanNew<String>("size"), NanNew<Integer>(cpuData.l2_cache));
		l2->Set(NanNew<String>("associativity"), NanNew<Integer>(cpuData.l2_assoc));
		l2->Set(NanNew<String>("cacheline"), NanNew<Integer>(cpuData.l2_cacheline));

		Local<Object> l3 = NanNew<Object>();
		cache->Set(NanNew<String>("l3"), l3);

		l3->Set(NanNew<String>("size"), NanNew<Integer>(cpuData.l3_cache));
		l3->Set(NanNew<String>("associativity"), NanNew<Integer>(cpuData.l3_assoc));
		l3->Set(NanNew<String>("cacheline"), NanNew<Integer>(cpuData.l3_cacheline));
	}

	static void fillId(Handle<Object> id, cpu_id_t& cpuData) {
		id->Set(NanNew<String>("family"), NanNew<Integer>(cpuData.family));
		id->Set(NanNew<String>("model"), NanNew<Integer>(cpuData.model));
		id->Set(NanNew<String>("stepping"), NanNew<Integer>(cpuData.stepping));
		id->Set(NanNew<String>("extFamily"), NanNew<Integer>(cpuData.ext_family));
		id->Set(NanNew<String>("extModel"), NanNew<Integer>(cpuData.ext_model));
	}

	static NAN_METHOD(GetCPUID) {
		NanScope();
		Local<Object> data = NanNew<Object>();

		if(!cpuid_present()) {
			return NanThrowTypeError("CPUID instruction not present");
		}

		cpu_raw_data_t raw;
		if(cpuid_get_raw_data(&raw) < 0) {
			return NanThrowTypeError("Could not execute CPUID");
		}

		cpu_id_t cpuData;
		if(cpu_identify(&raw, &cpuData) < 0) {
			return NanThrowTypeError("Could not parse CPUID data");
		}

		data->Set(NanNew<String>("vendorName"), NanNew<String>(cpuData.vendor_str));
		data->Set(NanNew<String>("vendor"), NanNew<String>(mapVendor(cpuData.vendor)));
		data->Set(NanNew<String>("vendorNumber"), NanNew<Integer>(cpuData.vendor));
		data->Set(NanNew<String>("brand"), NanNew<String>(cpuData.brand_str));
		data->Set(NanNew<String>("codeName"), NanNew<String>(cpuData.cpu_codename));
		data->Set(NanNew<String>("physicalCores"), NanNew<Integer>(cpuData.num_cores));
		data->Set(NanNew<String>("logicalCores"), NanNew<Integer>(cpuData.num_logical_cpus));
		data->Set(NanNew<String>("totalCores"), NanNew<Integer>(cpuData.total_logical_cpus));
		data->Set(NanNew<String>("clockSpeed"), NanNew<Integer>(cpu_clock()));

		Local<Object> features = NanNew<Object>();
		data->Set(NanNew<String>("features"), features);
		fillFeatures(features, cpuData);

		Local<Object> cache = NanNew<Object>();
		data->Set(NanNew<String>("cache"), cache);
		fillCache(cache, cpuData);

		Local<Object> id = NanNew<Object>();
		data->Set(NanNew<String>("id"), id);
		fillId(id, cpuData);

		NanReturnValue(data);
	}

	void CPUID::Initialize(Handle<Object> target) {
	  NanScope();
		NODE_SET_METHOD(target, "getCPUID", GetCPUID);
	}
}

NODE_MODULE(cpuid, cpuid::CPUID::Initialize)
