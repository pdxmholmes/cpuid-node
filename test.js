var cpuid = require('./build/Release/cpuid'),
	util = require('util');
console.log(util.inspect(cpuid.getCPUID()));