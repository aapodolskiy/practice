process.stdin.resume();
process.stdin.setEncoding('utf-8');

let t = 0;
let str = '';
let numberOfLinesRead = 0;
let ans = '';
 
process.stdin.on('data', input => {
    if (t === 0) {
        t = +input;
        return;
    }

    numberOfLinesRead++;

    main(input.trim());

    if (numberOfLinesRead === t) {
        console.log(ans);
        process.exit(0);
    }
});

const main = (str) => {
    ans += `len of ${str} is ${str.length} \n`;
}
