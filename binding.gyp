{
	"targets": [{
		"dependencies": [
			"deps/libcpuid/libcpuid.gyp:libcpuid"
		],

		'include_dirs': [
			'deps/libcpuid/libcpuid'
		],

		"target_name": "cpuid",
		"sources": [ "src/cpuid.cc" ]
	}]
}
