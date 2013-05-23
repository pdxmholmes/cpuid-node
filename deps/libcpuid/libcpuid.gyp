{
	'conditions': [
		['OS=="win"', {
			'target_defaults': {
				'rules': [ {
					'rule_name': 'assembler',
					'msvs_cygwin_shell': 0,
					'extension': 'asm',
					'outputs': [ '<(INTERMEDIATE_DIR)/<(RULE_INPUT_ROOT).obj', ],
					'action': [ 
						'ml64', '/c', '/Fo<(INTERMEDIATE_DIR)/<(RULE_INPUT_ROOT).obj', '<(RULE_INPUT_PATH)'
					],
					'message': 'Building assembly file <(RULE_INPUT_PATH)',
					'process_outputs_as_sources': 1,
				},
				],
			},
		}],
	],
	
	"targets": [{
		"target_name": "libcpuid",
		'type': 'static_library',
		
		'include_dirs': [
			'libcpuid'
		],

		'defines': [
			'VERSION="0.1.4"'
		],

		"sources": [ 
			"libcpuid/asm-bits.c",
			"libcpuid/cpuid_main.c",
			"libcpuid/libcpuid_util.c",
			"libcpuid/rdtsc.c",
			"libcpuid/recog_amd.c",
			"libcpuid/recog_intel.c"
		],

		"conditions": [
			['OS=="win"', {
				'defines': [ 'WIN32', '_LIB' ],
			
				'conditions': [
					['target_arch=="x64"', {
						'sources': [ 'libcpuid/masm-x64.asm' ]
					}]
				]
			}],
			['OS=="linux"', {
				'defines': ['HAVE_STDINT_H']
			}]
		]
	}]
}
