// @ts-ignore-next-line
process.stdin.resume();
// @ts-ignore-next-line
process.stdin.setEncoding("utf-8");

let input: string = "";
let inputData: string[];
let currentLineNumber = 0;

const getNextLine: () => string = () => inputData[currentLineNumber++];

// @ts-ignore-next-line
process.stdin.on("data", (d: string) => {
  input += d;
});

// @ts-ignore-next-line
process.stdin.on("end", () => {
  inputData = input
    .trim()
    .split("\n")
    .map((s) => s.trim());
  mainFunc();
});

///////////////////////////////////////////////////////////////////////////////

const isStringPalindrom = (s: string) =>
  s ===
  s
    .split("")
    .reverse()
    .join("");

const findAnswerValueForString = (s: string) => {
  let r = s.length;
  while (r > 1) {
    if (isStringPalindrom(s.slice(0, r))) {
      return r;
    }
    r--;
  }
  return 1;
};

const mainFunc = () => {
  let t = parseInt(getNextLine());

  while (t--) {
    const s = getNextLine();
    console.log(findAnswerValueForString(s));
  }
};
