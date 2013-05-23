#include <node.h>
#include <v8.h>
#include <libcpuid.h>
#include <strstream>
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
		features->Set(String::New("fpu"), Boolean::New(cpuData.flags[CPU_FEATURE_FPU]));
		features->Set(String::New("virtualModeExtension"), Boolean::New(cpuData.flags[CPU_FEATURE_VME]));
		features->Set(String::New("debuggingExtension"), Boolean::New(cpuData.flags[CPU_FEATURE_DE]));
		features->Set(String::New("pageSizeExtension"), Boolean::New(cpuData.flags[CPU_FEATURE_PSE]));
		features->Set(String::New("timeStampCounter"), Boolean::New(cpuData.flags[CPU_FEATURE_TSC]));
		features->Set(String::New("modelSpecificRegisters"), Boolean::New(cpuData.flags[CPU_FEATURE_MSR]));
		features->Set(String::New("physicalAddressExtension"), Boolean::New(cpuData.flags[CPU_FEATURE_PAE]));
		features->Set(String::New("machineCheckException"), Boolean::New(cpuData.flags[CPU_FEATURE_MCE]));
		features->Set(String::New("cx8Instruction"), Boolean::New(cpuData.flags[CPU_FEATURE_CX8]));
		features->Set(String::New("apic"), Boolean::New(cpuData.flags[CPU_FEATURE_APIC]));
		features->Set(String::New("mtrr"), Boolean::New(cpuData.flags[CPU_FEATURE_MTRR]));
		features->Set(String::New("sepInstructions"), Boolean::New(cpuData.flags[CPU_FEATURE_SEP]));
		features->Set(String::New("pageGlobalEnable"), Boolean::New(cpuData.flags[CPU_FEATURE_PGE]));
		features->Set(String::New("machineCheckArchitecture"), Boolean::New(cpuData.flags[CPU_FEATURE_MCA]));
		features->Set(String::New("cmovInstructions"), Boolean::New(cpuData.flags[CPU_FEATURE_CMOV]));
		features->Set(String::New("pageAttributeTable"), Boolean::New(cpuData.flags[CPU_FEATURE_PAT]));
		features->Set(String::New("pageAddressExtension36bit"), Boolean::New(cpuData.flags[CPU_FEATURE_PSE36]));
		features->Set(String::New("processorSerialNumber"), Boolean::New(cpuData.flags[CPU_FEATURE_PN]));
		features->Set(String::New("clflushInstruction"), Boolean::New(cpuData.flags[CPU_FEATURE_CLFLUSH]));
		features->Set(String::New("debugStore"), Boolean::New(cpuData.flags[CPU_FEATURE_DTS]));
		features->Set(String::New("acpi"), Boolean::New(cpuData.flags[CPU_FEATURE_ACPI]));
		features->Set(String::New("mmx"), Boolean::New(cpuData.flags[CPU_FEATURE_MMX]));
		features->Set(String::New("fxsrInstructions"), Boolean::New(cpuData.flags[CPU_FEATURE_FXSR]));
		features->Set(String::New("sse"), Boolean::New(cpuData.flags[CPU_FEATURE_SSE]));
		features->Set(String::New("sse2"), Boolean::New(cpuData.flags[CPU_FEATURE_SSE2]));
		features->Set(String::New("selfSnoop"), Boolean::New(cpuData.flags[CPU_FEATURE_SS]));
		features->Set(String::New("hyperthreading"), Boolean::New(cpuData.flags[CPU_FEATURE_HT]));
		features->Set(String::New("thermalMonitor"), Boolean::New(cpuData.flags[CPU_FEATURE_TM]));
		features->Set(String::New("ia64"), Boolean::New(cpuData.flags[CPU_FEATURE_IA64]));
		features->Set(String::New("pendingBreakEnable"), Boolean::New(cpuData.flags[CPU_FEATURE_PBE]));
		features->Set(String::New("sse3"), Boolean::New(cpuData.flags[CPU_FEATURE_PNI]));
		features->Set(String::New("pclmulInstruction"), Boolean::New(cpuData.flags[CPU_FEATURE_PCLMUL]));
		features->Set(String::New("debugStore64bit"), Boolean::New(cpuData.flags[CPU_FEATURE_DTS64]));
		features->Set(String::New("monitor"), Boolean::New(cpuData.flags[CPU_FEATURE_MONITOR]));
		features->Set(String::New("cplDebugStore"), Boolean::New(cpuData.flags[CPU_FEATURE_DS_CPL]));
		features->Set(String::New("virtualization"), Boolean::New(cpuData.flags[CPU_FEATURE_VMX]));
		features->Set(String::New("saferModeException"), Boolean::New(cpuData.flags[CPU_FEATURE_SMX]));
		features->Set(String::New("enhancedSpeedStep"), Boolean::New(cpuData.flags[CPU_FEATURE_EST]));
		features->Set(String::New("thermalMonitor2"), Boolean::New(cpuData.flags[CPU_FEATURE_TM2]));
		features->Set(String::New("ssse3Instructions"), Boolean::New(cpuData.flags[CPU_FEATURE_SSSE3]));
		features->Set(String::New("contextId"), Boolean::New(cpuData.flags[CPU_FEATURE_CID]));
		features->Set(String::New("cx16Instruction"), Boolean::New(cpuData.flags[CPU_FEATURE_CX16]));
		features->Set(String::New("tprDisable"), Boolean::New(cpuData.flags[CPU_FEATURE_XTPR]));
		features->Set(String::New("stpmDisable"), Boolean::New(cpuData.flags[CPU_FEATURE_XTPR]));
		features->Set(String::New("pdcm"), Boolean::New(cpuData.flags[CPU_FEATURE_PDCM]));
		features->Set(String::New("directCacheAccess"), Boolean::New(cpuData.flags[CPU_FEATURE_DCA]));
		features->Set(String::New("sse41"), Boolean::New(cpuData.flags[CPU_FEATURE_SSE4_1]));
		features->Set(String::New("sse42"), Boolean::New(cpuData.flags[CPU_FEATURE_SSE4_2]));
		features->Set(String::New("syscallInstructions"), Boolean::New(cpuData.flags[CPU_FEATURE_SYSCALL]));
		features->Set(String::New("executeDisableBit"), Boolean::New(cpuData.flags[CPU_FEATURE_XD]));
		features->Set(String::New("movbeInstruction"), Boolean::New(cpuData.flags[CPU_FEATURE_MOVBE]));
		features->Set(String::New("popcntInstruction"), Boolean::New(cpuData.flags[CPU_FEATURE_POPCNT]));
		features->Set(String::New("aesInstructions"), Boolean::New(cpuData.flags[CPU_FEATURE_AES]));
		features->Set(String::New("xsaveInstructions"), Boolean::New(cpuData.flags[CPU_FEATURE_XSAVE]));
		features->Set(String::New("osxsaveInstruction"), Boolean::New(cpuData.flags[CPU_FEATURE_OSXSAVE]));
		features->Set(String::New("avx"), Boolean::New(cpuData.flags[CPU_FEATURE_AVX]));
		features->Set(String::New("mmxExt"), Boolean::New(cpuData.flags[CPU_FEATURE_MMXEXT]));
		features->Set(String::New("amd3dNow"), Boolean::New(cpuData.flags[CPU_FEATURE_3DNOW]));
		features->Set(String::New("amd3dNowExt"), Boolean::New(cpuData.flags[CPU_FEATURE_3DNOWEXT]));
		features->Set(String::New("noExecuteBit"), Boolean::New(cpuData.flags[CPU_FEATURE_NX]));
		features->Set(String::New("fxsrOptimizations"), Boolean::New(cpuData.flags[CPU_FEATURE_FXSR_OPT]));
		features->Set(String::New("rdtscpInstruction"), Boolean::New(cpuData.flags[CPU_FEATURE_RDTSCP]));
		features->Set(String::New("em64t"), Boolean::New(cpuData.flags[CPU_FEATURE_LM]));
		features->Set(String::New("x86_64"), Boolean::New(cpuData.flags[CPU_FEATURE_LM]));
		features->Set(String::New("lahf64bit"), Boolean::New(cpuData.flags[CPU_FEATURE_LAHF_LM]));
		features->Set(String::New("cmpLegacy"), Boolean::New(cpuData.flags[CPU_FEATURE_CMP_LEGACY]));
		features->Set(String::New("secureVirtualMachine"), Boolean::New(cpuData.flags[CPU_FEATURE_SVM]));
		features->Set(String::New("lzcntInstruction"), Boolean::New(cpuData.flags[CPU_FEATURE_ABM]));
		features->Set(String::New("misalignedSSE"), Boolean::New(cpuData.flags[CPU_FEATURE_MISALIGNSSE]));
		features->Set(String::New("sse4a"), Boolean::New(cpuData.flags[CPU_FEATURE_SSE4A]));		
		features->Set(String::New("amd3dNowPrefetch"), Boolean::New(cpuData.flags[CPU_FEATURE_3DNOWPREFETCH]));
		features->Set(String::New("osVisibleWorkaround"), Boolean::New(cpuData.flags[CPU_FEATURE_OSVW]));
		features->Set(String::New("instructionBasedSampling"), Boolean::New(cpuData.flags[CPU_FEATURE_IBS]));
		features->Set(String::New("sse5"), Boolean::New(cpuData.flags[CPU_FEATURE_SSE5]));
		features->Set(String::New("skinitInstructions"), Boolean::New(cpuData.flags[CPU_FEATURE_SKINIT]));
		features->Set(String::New("watchdogTimer"), Boolean::New(cpuData.flags[CPU_FEATURE_WDT]));
		features->Set(String::New("temperatureSensor"), Boolean::New(cpuData.flags[CPU_FEATURE_TS]));
		features->Set(String::New("frequencyIDControl"), Boolean::New(cpuData.flags[CPU_FEATURE_FID]));
		features->Set(String::New("voltageIDControl"), Boolean::New(cpuData.flags[CPU_FEATURE_VID]));
		features->Set(String::New("thermtrip"), Boolean::New(cpuData.flags[CPU_FEATURE_TTP]));
		features->Set(String::New("amdThermalControl"), Boolean::New(cpuData.flags[CPU_FEATURE_TM_AMD]));
		features->Set(String::New("softwareThermalControl"), Boolean::New(cpuData.flags[CPU_FEATURE_STC]));
		features->Set(String::New("multiplierSteps100mhz"), Boolean::New(cpuData.flags[CPU_FEATURE_100MHZSTEPS]));
		features->Set(String::New("hardwarePState"), Boolean::New(cpuData.flags[CPU_FEATURE_HWPSTATE]));
		features->Set(String::New("constantTSCTicks"), Boolean::New(cpuData.flags[CPU_FEATURE_CONSTANT_TSC]));
	}

	static void fillCache(Handle<Object> cache, cpu_id_t& cpuData) {
		Local<Object> l1 = Object::New();
		cache->Set(String::New("l1"), l1);

		l1->Set(String::New("data"), Integer::New(cpuData.l1_data_cache));
		l1->Set(String::New("instruction"), Integer::New(cpuData.l1_instruction_cache));
		l1->Set(String::New("associativity"), Integer::New(cpuData.l1_assoc));
		l1->Set(String::New("cacheline"), Integer::New(cpuData.l1_cacheline));

		Local<Object> l2 = Object::New();
		cache->Set(String::New("l2"), l2);

		l2->Set(String::New("size"), Integer::New(cpuData.l2_cache));
		l2->Set(String::New("associativity"), Integer::New(cpuData.l2_assoc));
		l2->Set(String::New("cacheline"), Integer::New(cpuData.l2_cacheline));

		Local<Object> l3 = Object::New();
		cache->Set(String::New("l3"), l3);

		l3->Set(String::New("size"), Integer::New(cpuData.l3_cache));
		l3->Set(String::New("associativity"), Integer::New(cpuData.l3_assoc));
		l3->Set(String::New("cacheline"), Integer::New(cpuData.l3_cacheline));
	}

	static void fillId(Handle<Object> id, cpu_id_t& cpuData) {
		id->Set(String::New("family"), Integer::New(cpuData.family));
		id->Set(String::New("model"), Integer::New(cpuData.model));
		id->Set(String::New("stepping"), Integer::New(cpuData.stepping));
		id->Set(String::New("extFamily"), Integer::New(cpuData.ext_family));
		id->Set(String::New("extModel"), Integer::New(cpuData.ext_model));
	}

	static Handle<Value> GetCPUID(const Arguments& args) {
		HandleScope scope;
		Local<Object> data = Object::New();

		if(!cpuid_present()) {
			return ThrowException(Exception::TypeError(String::New("CPUID instruction not present")));
		}

		cpu_raw_data_t raw;
		if(cpuid_get_raw_data(&raw) < 0) {
			return ThrowException(Exception::TypeError(String::New("Could not execute CPUID")));
		}

		cpu_id_t cpuData;
		if(cpu_identify(&raw, &cpuData) < 0) {
			return ThrowException(Exception::TypeError(String::New("Could not parse CPUID data")));
		}

		data->Set(String::New("vendorName"), String::New(cpuData.vendor_str));
		data->Set(String::New("vendor"), String::New(mapVendor(cpuData.vendor)));
		data->Set(String::New("vendorNumber"), Integer::New(cpuData.vendor));
		data->Set(String::New("brand"), String::New(cpuData.brand_str));
		data->Set(String::New("codeName"), String::New(cpuData.cpu_codename));
		data->Set(String::New("physicalCores"), Integer::New(cpuData.num_cores));
		data->Set(String::New("logicalCores"), Integer::New(cpuData.num_logical_cpus));
		data->Set(String::New("totalCores"), Integer::New(cpuData.total_logical_cpus));

		Local<Object> features = Object::New();
		data->Set(String::New("features"), features);
		fillFeatures(features, cpuData);

		Local<Object> cache = Object::New();
		data->Set(String::New("cache"), cache);
		fillCache(cache, cpuData);

		Local<Object> id = Object::New();
		data->Set(String::New("id"), id);
		fillId(id, cpuData);

		return scope.Close(data);
	}	

	void CPUID::Initialize(Handle<Object> target) {
		HandleScope scope;
		NODE_SET_METHOD(target, "getCPUID", GetCPUID);
	}
}

NODE_MODULE(cpuid, cpuid::CPUID::Initialize)