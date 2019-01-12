{
	"targets": [{
		"dependencies": [
			"deps/libcpuid/libcpuid.gyp:libcpuid"
		],

		'include_dirs': [
			"<!(node -e \"require('nan')\")",
			'deps/libcpuid/libcpuid'
		],

		"target_name": "cpuid",
		"sources": [ "src/cpuid.cc" ],

		"win_delay_load_hook": 'true',

		"conditions": [
			['OS=="linux"', {
				'defines': ['HAVE_STDINT_H']
			}]
		]
	}]
}
