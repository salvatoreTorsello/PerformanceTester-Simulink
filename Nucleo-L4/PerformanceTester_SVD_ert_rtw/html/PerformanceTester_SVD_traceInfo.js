function RTW_rtwnameSIDMap() {
	this.rtwnameHashMap = new Array();
	this.sidHashMap = new Array();
	this.rtwnameHashMap["<Root>"] = {sid: "PerformanceTester_SVD"};
	this.sidHashMap["PerformanceTester_SVD"] = {rtwname: "<Root>"};
	this.rtwnameHashMap["<Root>/Inport"] = {sid: "PerformanceTester_SVD:3"};
	this.sidHashMap["PerformanceTester_SVD:3"] = {rtwname: "<Root>/Inport"};
	this.rtwnameHashMap["<Root>/Singular Value Decomposition"] = {sid: "PerformanceTester_SVD:2"};
	this.sidHashMap["PerformanceTester_SVD:2"] = {rtwname: "<Root>/Singular Value Decomposition"};
	this.rtwnameHashMap["<Root>/Outport"] = {sid: "PerformanceTester_SVD:4"};
	this.sidHashMap["PerformanceTester_SVD:4"] = {rtwname: "<Root>/Outport"};
	this.rtwnameHashMap["<Root>/Outport1"] = {sid: "PerformanceTester_SVD:5"};
	this.sidHashMap["PerformanceTester_SVD:5"] = {rtwname: "<Root>/Outport1"};
	this.rtwnameHashMap["<Root>/Outport2"] = {sid: "PerformanceTester_SVD:6"};
	this.sidHashMap["PerformanceTester_SVD:6"] = {rtwname: "<Root>/Outport2"};
	this.getSID = function(rtwname) { return this.rtwnameHashMap[rtwname];}
	this.getRtwname = function(sid) { return this.sidHashMap[sid];}
}
RTW_rtwnameSIDMap.instance = new RTW_rtwnameSIDMap();
