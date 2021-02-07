'use strict';

process.stdin.resume();
process.stdin.setEncoding('utf-8');

let inputString = '';
let currentLine = 0;

const getLine = () => inputString[currentLine++];
 
process.stdin.on('data', d => {
    inputString += d;
});

process.stdin.on('end', _ => {
    inputString = inputString.trim().split('\n').map(s => s.trim());
    main();
});

///////////////////////////////////////////////////////////////////////////////

const isPalindrom = s =>
    s === s.split("").reverse().join("");

const findValueForString = s => {
    let r = s.length;
    while (r > 1) {
        if (isPalindrom(s.slice(0, r))) {
            return r;
        }
        r--;
    }
    return 1;
}

const main = () => {
    let t = parseInt(getLine());

    while (t--) {
        const s = getLine();
        console.log(findValueForString(s));
    }
}
