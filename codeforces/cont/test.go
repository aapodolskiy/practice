package main
 
import (
    "bufio"
    "flag"
    "fmt"
    "log"
    "os"
    "runtime/pprof"
    "strconv"
    "strings"
)

var cpuprofile = flag.String("cpuprofile", "", "write cpu profile to file")

func f(a, b []int, n int) int {
	sumA, sumB, S := 0, 0, 0
	for i := 0; i < n; i++ {
		sumA += a[i]
		sumB += b[i]
		if a[i] != b[i] {
			S++
		}
	}
	res := abs(sumA - sumB)
	if S > 0 {
		res++
	}
	return min(res, S)
}

func main() {
    flag.Parse()
    if *cpuprofile != "" {
        f, err := os.Create(*cpuprofile)
        if err != nil {
            log.Fatal(err)
        }
        pprof.StartCPUProfile(f)
        defer pprof.StopCPUProfile()
    }

    in := bufio.NewReader(os.Stdin)
    tc := readInt(in)

	for i := 0; i < tc; i++ {
        n := readInt(in)
        a := readArrInt(in)
		b := readArrInt(in)
        fmt.Println(f(a, b, n))
	}
}

func readInt(in *bufio.Reader) int {
	nStr, _ := in.ReadString('\n')
	nStr = strings.ReplaceAll(nStr, "\r", "")
	nStr = strings.ReplaceAll(nStr, "\n", "")
	n, _ := strconv.Atoi(nStr)
	return n
}

func readLineNumbs(in *bufio.Reader) []string {
	line, _ := in.ReadString('\n')
	line = strings.ReplaceAll(line, "\r", "")
	line = strings.ReplaceAll(line, "\n", "")
	numbs := strings.Split(line, " ")
	return numbs
}

func readArrInt(in *bufio.Reader) []int {
	numbs := readLineNumbs(in)
	arr := make([]int, len(numbs))
	for i, n := range numbs {
		val, _ := strconv.Atoi(n)
		arr[i] = val
	}
	return arr
}

func readArrInt64(in *bufio.Reader) []int64 {
	numbs := readLineNumbs(in)
	arr := make([]int64, len(numbs))
	for i, n := range numbs {
		val, _ := strconv.ParseInt(n, 10, 64)
		arr[i] = val
	}
	return arr
}

func abs(x int) int {
	if x < 0 { return -x }
	return x
}

func min(x, y int) int {
	if x < y { return x }
	return y
}

func max(x, y int) int {
	if x < y { return x }
	return x
}
