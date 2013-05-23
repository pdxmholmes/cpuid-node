var cpuid;
try {
	cpuid = require('../build/Release/cpuid');
} 
catch (e) { 
	try {
		cpuid = require('../build/default/cpuid');
	} 
	catch (e) { 
		console.error('cpuid.node seems to not have been built. Run npm install.');
		throw e;
	}
}

module.exports = function() {
	return cpuid.getCPUID();
}
