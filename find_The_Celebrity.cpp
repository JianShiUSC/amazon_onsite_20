bool knows(int a, int b);

// O(n), O(1)
class Solution {
public:
    int findCelebrity(int n) {
        int begin = 0;
        int end = n - 1;

        while(begin < end) {
            if(knows(begin, end)) begin++;
            else end--;
        }

        for(int i = 0; i < n; i++) {
            if(!knows(i, begin) || i != begin && knows(begin, i)) return -1;
        }
        return begin;
    }
};

// O(n), O(1)   面试时解法不正确，找到celebrity后没check明星认不认识其他人
class Solution {
public:
    int findCelebrity(int n) {
        int candidate = 0;
        for(int i = 1; i < n; i++) {
            if(knows(candidate, i)) {
                candidate = i;
            }
        }
        for(int i = 0; i < n; i++) {
            if(!knows(i, candidate) || i != candidate && knows(candidate, i)) return -1;
        }
        return candidate;
    }
};

// O(n^2), O(n)
class Solution {
public:
    int findCelebrity(int n) {
        if(n <= 1) return -1;
        vector<int> inDegree(n, 0);
        vector<int> outDegree(n, 0);

        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(i != j && knows(i, j)) {
                    outDegree[i]++;
                    inDegree[j]++;
                }
            }
        }

        for(int i = 0; i < n; i++) {
            if(inDegree[i] == n-1 && outDegree[i] == 0) return i;
        }
        return -1;
    }
};

// O(n), O(n)
class Solution {
public:
    int findCelebrity(int n) {
        stack<int> stk;
        int celebrity = 0;

        for(int i = 0; i < n; i++) {
            stk.push(i);
        }

        int A = stk.top();
        stk.pop();
        int B = stk.top();
        stk.pop();

        while(stk.size() > 1) {
            if(knows(A, B)) {
                A = stk.top();
                stk.pop();
            } else {
                B = stk.top();
                stk.pop();
            }
        }

        if(!stk.empty()) {
            celebrity = stk.top();
            stk.pop();
        }

        if(knows(celebrity, B)) celebrity = B;
        if(knows(celebrity, A)) celebrity = A;

        for(int i = 0; i < n; i++) {
            if(!knows(i, celebrity) || i != celebrity && knows(celebrity, i)) return -1;
        }
        return celebrity;
    }
};
