#include <nan.h>
#include <libcpuid.h>

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
	features->Set(Nan::New("fpu").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_FPU]));
	features->Set(Nan::New("virtualModeExtension").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_VME]));
	features->Set(Nan::New("debuggingExtension").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_DE]));
	features->Set(Nan::New("pageSizeExtension").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_PSE]));
	features->Set(Nan::New("timeStampCounter").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_TSC]));
	features->Set(Nan::New("modelSpecificRegisters").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_MSR]));
	features->Set(Nan::New("physicalAddressExtension").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_PAE]));
	features->Set(Nan::New("machineCheckException").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_MCE]));
	features->Set(Nan::New("cx8Instruction").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_CX8]));
	features->Set(Nan::New("apic").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_APIC]));
	features->Set(Nan::New("mtrr").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_MTRR]));
	features->Set(Nan::New("sepInstructions").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_SEP]));
	features->Set(Nan::New("pageGlobalEnable").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_PGE]));
	features->Set(Nan::New("machineCheckArchitecture").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_MCA]));
	features->Set(Nan::New("cmovInstructions").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_CMOV]));
	features->Set(Nan::New("pageAttributeTable").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_PAT]));
	features->Set(Nan::New("pageAddressExtension36bit").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_PSE36]));
	features->Set(Nan::New("processorSerialNumber").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_PN]));
	features->Set(Nan::New("clflushInstruction").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_CLFLUSH]));
	features->Set(Nan::New("debugStore").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_DTS]));
	features->Set(Nan::New("acpi").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_ACPI]));
	features->Set(Nan::New("mmx").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_MMX]));
	features->Set(Nan::New("fxsrInstructions").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_FXSR]));
	features->Set(Nan::New("sse").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_SSE]));
	features->Set(Nan::New("sse2").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_SSE2]));
	features->Set(Nan::New("selfSnoop").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_SS]));
	features->Set(Nan::New("hyperthreading").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_HT]));
	features->Set(Nan::New("thermalMonitor").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_TM]));
	features->Set(Nan::New("ia64").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_IA64]));
	features->Set(Nan::New("pendingBreakEnable").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_PBE]));
	features->Set(Nan::New("sse3").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_PNI]));
	features->Set(Nan::New("pclmulInstruction").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_PCLMUL]));
	features->Set(Nan::New("debugStore64bit").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_DTS64]));
	features->Set(Nan::New("monitor").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_MONITOR]));
	features->Set(Nan::New("cplDebugStore").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_DS_CPL]));
	features->Set(Nan::New("virtualization").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_VMX]));
	features->Set(Nan::New("saferModeException").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_SMX]));
	features->Set(Nan::New("enhancedSpeedStep").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_EST]));
	features->Set(Nan::New("thermalMonitor2").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_TM2]));
	features->Set(Nan::New("ssse3Instructions").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_SSSE3]));
	features->Set(Nan::New("contextId").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_CID]));
	features->Set(Nan::New("cx16Instruction").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_CX16]));
	features->Set(Nan::New("tprDisable").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_XTPR]));
	features->Set(Nan::New("stpmDisable").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_XTPR]));
	features->Set(Nan::New("pdcm").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_PDCM]));
	features->Set(Nan::New("directCacheAccess").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_DCA]));
	features->Set(Nan::New("sse41").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_SSE4_1]));
	features->Set(Nan::New("sse42").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_SSE4_2]));
	features->Set(Nan::New("syscallInstructions").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_SYSCALL]));
	features->Set(Nan::New("executeDisableBit").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_XD]));
	features->Set(Nan::New("movbeInstruction").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_MOVBE]));
	features->Set(Nan::New("popcntInstruction").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_POPCNT]));
	features->Set(Nan::New("aesInstructions").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_AES]));
	features->Set(Nan::New("xsaveInstructions").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_XSAVE]));
	features->Set(Nan::New("osxsaveInstruction").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_OSXSAVE]));
	features->Set(Nan::New("avx").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_AVX]));
	features->Set(Nan::New("mmxExt").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_MMXEXT]));
	features->Set(Nan::New("amd3dNow").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_3DNOW]));
	features->Set(Nan::New("amd3dNowExt").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_3DNOWEXT]));
	features->Set(Nan::New("noExecuteBit").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_NX]));
	features->Set(Nan::New("fxsrOptimizations").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_FXSR_OPT]));
	features->Set(Nan::New("rdtscpInstruction").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_RDTSCP]));
	features->Set(Nan::New("em64t").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_LM]));
	features->Set(Nan::New("x86_64").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_LM]));
	features->Set(Nan::New("lahf64bit").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_LAHF_LM]));
	features->Set(Nan::New("cmpLegacy").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_CMP_LEGACY]));
	features->Set(Nan::New("secureVirtualMachine").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_SVM]));
	features->Set(Nan::New("lzcntInstruction").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_ABM]));
	features->Set(Nan::New("misalignedSSE").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_MISALIGNSSE]));
	features->Set(Nan::New("sse4a").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_SSE4A]));
	features->Set(Nan::New("amd3dNowPrefetch").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_3DNOWPREFETCH]));
	features->Set(Nan::New("osVisibleWorkaround").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_OSVW]));
	features->Set(Nan::New("instructionBasedSampling").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_IBS]));
	features->Set(Nan::New("sse5").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_SSE5]));
	features->Set(Nan::New("skinitInstructions").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_SKINIT]));
	features->Set(Nan::New("watchdogTimer").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_WDT]));
	features->Set(Nan::New("temperatureSensor").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_TS]));
	features->Set(Nan::New("frequencyIDControl").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_FID]));
	features->Set(Nan::New("voltageIDControl").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_VID]));
	features->Set(Nan::New("thermtrip").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_TTP]));
	features->Set(Nan::New("amdThermalControl").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_TM_AMD]));
	features->Set(Nan::New("softwareThermalControl").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_STC]));
	features->Set(Nan::New("multiplierSteps100mhz").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_100MHZSTEPS]));
	features->Set(Nan::New("hardwarePState").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_HWPSTATE]));
	features->Set(Nan::New("constantTSCTicks").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_CONSTANT_TSC]));
}

static void fillCache(Handle<Object> cache, cpu_id_t& cpuData) {
	Local<Object> l1 = Nan::New<Object>();
	cache->Set(Nan::New("l1").ToLocalChecked(), l1);

	l1->Set(Nan::New("data").ToLocalChecked(), Nan::New(cpuData.l1_data_cache));
	l1->Set(Nan::New("instruction").ToLocalChecked(), Nan::New(cpuData.l1_instruction_cache));
	l1->Set(Nan::New("associativity").ToLocalChecked(), Nan::New(cpuData.l1_assoc));
	l1->Set(Nan::New("cacheline").ToLocalChecked(), Nan::New(cpuData.l1_cacheline));

	Local<Object> l2 = Nan::New<Object>();
	cache->Set(Nan::New("l2").ToLocalChecked(), l2);

	l2->Set(Nan::New("size").ToLocalChecked(), Nan::New(cpuData.l2_cache));
	l2->Set(Nan::New("associativity").ToLocalChecked(), Nan::New(cpuData.l2_assoc));
	l2->Set(Nan::New("cacheline").ToLocalChecked(), Nan::New(cpuData.l2_cacheline));

	Local<Object> l3 = Nan::New<Object>();
	cache->Set(Nan::New("l3").ToLocalChecked(), l3);

	l3->Set(Nan::New("size").ToLocalChecked(), Nan::New(cpuData.l3_cache));
	l3->Set(Nan::New("associativity").ToLocalChecked(), Nan::New(cpuData.l3_assoc));
	l3->Set(Nan::New("cacheline").ToLocalChecked(), Nan::New(cpuData.l3_cacheline));
}

static void fillId(Handle<Object> id, cpu_id_t& cpuData) {
	id->Set(Nan::New("family").ToLocalChecked(), Nan::New(cpuData.family));
	id->Set(Nan::New("model").ToLocalChecked(), Nan::New(cpuData.model));
	id->Set(Nan::New("stepping").ToLocalChecked(), Nan::New(cpuData.stepping));
	id->Set(Nan::New("extFamily").ToLocalChecked(), Nan::New(cpuData.ext_family));
	id->Set(Nan::New("extModel").ToLocalChecked(), Nan::New(cpuData.ext_model));
}



NAN_METHOD(GetCPUID) {
	if(!cpuid_present()) {
		return Nan::ThrowError("CPUID instruction not available");
	}

	cpu_raw_data_t raw;
	if(cpuid_get_raw_data(&raw) < 0) {
		return Nan::ThrowError("Could not execute CPUID");
	}

	cpu_id_t cpuData;
	if(cpu_identify(&raw, &cpuData) < 0) {
		return Nan::ThrowError("Could not parse CPUID data");
	}

	Local<Object> data = Nan::New<Object>();
	data->Set(Nan::New("vendorName").ToLocalChecked(), Nan::New(cpuData.vendor_str).ToLocalChecked());
	data->Set(Nan::New("vendor").ToLocalChecked(), Nan::New(mapVendor(cpuData.vendor)).ToLocalChecked());
	data->Set(Nan::New("vendorNumber").ToLocalChecked(), Nan::New(cpuData.vendor));
	data->Set(Nan::New("brand").ToLocalChecked(), Nan::New(cpuData.brand_str).ToLocalChecked());
	data->Set(Nan::New("codeName").ToLocalChecked(), Nan::New(cpuData.cpu_codename).ToLocalChecked());
	data->Set(Nan::New("physicalCores").ToLocalChecked(), Nan::New(cpuData.num_cores));
	data->Set(Nan::New("logicalCores").ToLocalChecked(), Nan::New(cpuData.num_logical_cpus));
	data->Set(Nan::New("totalCores").ToLocalChecked(), Nan::New(cpuData.total_logical_cpus));
	data->Set(Nan::New("clockSpeed").ToLocalChecked(), Nan::New(cpu_clock()));

	Local<Object> features = Nan::New<Object>();
	data->Set(Nan::New("features").ToLocalChecked(), features);
	fillFeatures(features, cpuData);

	Local<Object> cache = Nan::New<Object>();
	data->Set(Nan::New("cache").ToLocalChecked(), cache);
	fillCache(cache, cpuData);

	Local<Object> id = Nan::New<Object>();
	data->Set(Nan::New("id").ToLocalChecked(), id);
	fillId(id, cpuData);

	info.GetReturnValue().Set(data);
}

NAN_MODULE_INIT(InitAll) {
	Nan::Set(target, Nan::New("getCPUID").ToLocalChecked(),
		Nan::GetFunction(Nan::New<FunctionTemplate>(GetCPUID)).ToLocalChecked());
}

NODE_MODULE(cpuid, InitAll)
