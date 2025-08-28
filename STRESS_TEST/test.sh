set -e
g++ gen.cpp -o gen
g++ brute.cpp -o brute
for((i = 1; ; ++i)); do
    ./gen $i > stress
    ./a.exe < stress > myAnswer
    ./brute < stress > correctAnswer
    diff -Z myAnswer correctAnswer > /dev/null || break
    echo "Passed test: " $i
done
echo "WA on the following test:"
cat stress
echo "Your answer is:"
cat myAnswer
echo "Correct answer is:"
cat correctAnswer