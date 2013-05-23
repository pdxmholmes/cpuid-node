#include <node.h>
#include <v8.h>
#include <libcpuid.h>
#include "cpuid.h"

namespace cpuid {
	using namespace v8;

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

		data->Set(String::New("vendor"), String::New(cpuData.vendor_str));
		data->Set(String::New("brand"), String::New(cpuData.brand_str));
		data->Set(String::New("codeName"), String::New(cpuData.cpu_codename));
		data->Set(String::New("cores"), Integer::New(cpuData.num_cores));
		data->Set(String::New("logicalCores"), Integer::New(cpuData.num_logical_cpus));
		data->Set(String::New("totalCores"), Integer::New(cpuData.total_logical_cpus));

		Local<Object> flags = Object::New();
		data->Set(String::New("flags"), flags);

		flags->Set(String::New("fpu"), Boolean::New(cpuData.flags[CPU_FEATURE_FPU]));
		flags->Set(String::New("virtualModeExtension"), Boolean::New(cpuData.flags[CPU_FEATURE_VME]));
		flags->Set(String::New("debuggingExtension"), Boolean::New(cpuData.flags[CPU_FEATURE_DE]));
		flags->Set(String::New("pageSizeExtension"), Boolean::New(cpuData.flags[CPU_FEATURE_PSE]));
		flags->Set(String::New("timeStampCounter"), Boolean::New(cpuData.flags[CPU_FEATURE_TSC]));
		flags->Set(String::New("modelSpecificRegisters"), Boolean::New(cpuData.flags[CPU_FEATURE_MSR]));
		flags->Set(String::New("physicalAddressExtension"), Boolean::New(cpuData.flags[CPU_FEATURE_PAE]));
		flags->Set(String::New("machineCheckException"), Boolean::New(cpuData.flags[CPU_FEATURE_MCE]));
		flags->Set(String::New("cx8"), Boolean::New(cpuData.flags[CPU_FEATURE_CX8]));
		flags->Set(String::New("apic"), Boolean::New(cpuData.flags[CPU_FEATURE_APIC]));
		flags->Set(String::New("hyperthreading"), Boolean::New(cpuData.flags[CPU_FEATURE_HT]));
		flags->Set(String::New("ia64"), Boolean::New(cpuData.flags[CPU_FEATURE_IA64]));

		Local<Object> cache = Object::New();
		data->Set(String::New("cache"), cache);

		return scope.Close(data);
	}

	void CPUID::Initialize(Handle<Object> target) {
		HandleScope scope;
		NODE_SET_METHOD(target, "getCPUID", GetCPUID);
	}
}

NODE_MODULE(cpuid, cpuid::CPUID::Initialize)