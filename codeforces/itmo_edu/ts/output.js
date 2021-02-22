// @ts-ignore-next-line
process.stdin.resume();
// @ts-ignore-next-line
process.stdin.setEncoding("utf-8");
var input = "";
var inputData;
var currentLineNumber = 0;
var getNextLine = function getNextLine() {
    return inputData[currentLineNumber++];
};
// @ts-ignore-next-line
process.stdin.on("data", function(d) {
    input += d;
});
// @ts-ignore-next-line
process.stdin.on("end", function() {
    inputData = input.trim().split("\n").map(function(s) {
        return s.trim();
    });
    mainFunc();
});
///////////////////////////////////////////////////////////////////////////////
var isStringPalindrom = function isStringPalindrom(s) {
    return s === s.split("").reverse().join("");
};
var findAnswerValueForString = function findAnswerValueForString(s) {
    var r = s.length;
    while(r > 1){
        if (isStringPalindrom(s.slice(0, r))) {
            return r;
        }
        r--;
    }
    return 1;
};
var mainFunc = function mainFunc() {
    var t = parseInt(getNextLine());
    while(t--){
        var s = getNextLine();
        console.log(findAnswerValueForString(s));
    }
};

