cpuid
==========

cpuid is a simple to user wrapper around [LibCPUID](http://libcpuid.sourceforge.net/) for [Node.js](http://www.nodejs.org). It's so simple in fact, it's exactly one function, which returns a very easy to use object graph.

cpuid has been tested on Windows 64-bit, Macintosh OSX (Darwin) 64-bit and Linux 3.x 64-bit. All 32-bit platforms should work, but I have not tested them. If you do and it does not work, please file a bug report.

cpuid requires a natively compiled binary component, so it is not suitable for usage in the browser environment.

cpuid's most useful feature for many Node users will be it's detailed overview of the logical versus physical cores. As things like [cluster](http://www.nodejs.org/api/cluster.html) come to the forefront, and "multi-threaded Node" becomes a reality, this information can be invaluable for worker pool performance.

usage
==========

```JavaScript
var cpuid = require('cpuid');
var cpuidInfo = cpuid();
```

cpuid is one function, which takes no arguments, and returns an object with properties representing the CPUID data. As an example, here is the CPUID information for my development computer:

```JavaScript
{ vendorName: 'GenuineIntel',
  vendor: 'intel',
  vendorNumber: 0,
  brand: 'Intel(R) Core(TM) i5-2500K CPU @ 3.30GHz',
  codeName: 'Sandy Bridge (Core i5)',
  physicalCores: 4,
  logicalCores: 4,
  totalCores: 4,
  clockSpeed: 3293,
  features: 
   { fpu: true,
     virtualModeExtension: true,
     debuggingExtension: true,
     pageSizeExtension: true,
     timeStampCounter: true,
     modelSpecificRegisters: true,
     physicalAddressExtension: true,
     machineCheckException: true,
     cx8Instruction: true,
     apic: true,
     mtrr: true,
     sepInstructions: true,
     pageGlobalEnable: true,
     machineCheckArchitecture: true,
     cmovInstructions: true,
     pageAttributeTable: true,
     pageAddressExtension36bit: true,
     processorSerialNumber: false,
     clflushInstruction: true,
     debugStore: true,
     acpi: true,
     mmx: true,
     fxsrInstructions: true,
     sse: true,
     sse2: true,
     selfSnoop: true,
     hyperthreading: true,
     thermalMonitor: true,
     ia64: false,
     pendingBreakEnable: true,
     sse3: true,
     pclmulInstruction: true,
     debugStore64bit: true,
     monitor: true,
     cplDebugStore: true,
     virtualization: true,
     saferModeException: false,
     enhancedSpeedStep: true,
     thermalMonitor2: true,
     ssse3Instructions: true,
     contextId: false,
     cx16Instruction: true,
     tprDisable: true,
     stpmDisable: true,
     pdcm: true,
     directCacheAccess: false,
     sse41: true,
     sse42: true,
     syscallInstructions: true,
     executeDisableBit: true,
     movbeInstruction: false,
     popcntInstruction: true,
     aesInstructions: true,
     xsaveInstructions: true,
     osxsaveInstruction: true,
     avx: true,
     mmxExt: false,
     amd3dNow: false,
     amd3dNowExt: false,
     noExecuteBit: false,
     fxsrOptimizations: false,
     rdtscpInstruction: false,
     em64t: true,
     x86_64: true,
     lahf64bit: true,
     cmpLegacy: false,
     secureVirtualMachine: false,
     lzcntInstruction: false,
     misalignedSSE: false,
     sse4a: false,
     amd3dNowPrefetch: false,
     osVisibleWorkaround: false,
     instructionBasedSampling: false,
     sse5: false,
     skinitInstructions: false,
     watchdogTimer: false,
     temperatureSensor: false,
     frequencyIDControl: false,
     voltageIDControl: false,
     thermtrip: false,
     amdThermalControl: false,
     softwareThermalControl: false,
     multiplierSteps100mhz: false,
     hardwarePState: false,
     constantTSCTicks: false },
  cache: 
   { l1: { data: 32, instruction: 32, associativity: 8, cacheline: 64 },
     l2: { size: 256, associativity: 8, cacheline: 64 },
     l3: { size: 6144, associativity: 12, cacheline: 64 } },
  id: { family: 6, model: 10, stepping: 7, extFamily: 6, extModel: 42 } }
```

property documentation
==========

Coming Soon
