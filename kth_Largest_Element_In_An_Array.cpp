// O(nlogn), O(logn)
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        int size = nums.size();
        sort(nums.begin(), nums.end());
        return nums[size - k];
    }
};

// naive max heap, O(nlogn), O(n)
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int> pq(nums.begin(), nums.end());
        for(int i = 0; i < k - 1; i++) {
            pq.pop();
        }
        return pq.top();
    }
};

// min heap, O(nlogk), O(k)
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int, vector<int>, greater<int>> pq;  // min heap
        for(int num : nums) {
            pq.push(num);
            if(pq.size() > k) pq.pop();
        }
        return pq.top();
    }
};

// max heap, O(n + klogn), O(1)
class Solution {
private:
    int heap_size;
public:
    int getLeft(int idx) {              // because idx is zero-based
        return (idx << 1) + 1;
    }
    int getRight(int idx) {
        return (idx << 1) + 2;
    }
    void max_heapify(vector<int>& nums, int idx) {
        int largest = idx;
        int l = getLeft(idx), r = getRight(idx);
        if(l < heap_size && nums[l] > nums[largest]) largest = l;
        if(r < heap_size && nums[r] > nums[largest]) largest = r;
        if(largest != idx) {
            swap(nums[idx], nums[largest]);
            max_heapify(nums, largest);
        }
    }
    void build_max_heap(vector<int>& nums) {
        heap_size = nums.size();
        for(int i = (heap_size >> 1) - 1; i >= 0; i--) {            // nums[0...n - 1], for i = n / 2 - 1 down to 0, do Max_Heapify(A, i)
                                                                    // Why start at n / 2 - 1?
                                                                    // Because elements A[n/2 ... n - 1] are all leaves of the
                                                                    // tree 2i + 1 > n - 1, for i > n / 2 - 1, i >= n / 2;
            max_heapify(nums, i);
        }
    }
    int findKthLargest(vector<int>& nums, int k) {
        build_max_heap(nums);
        for(int i = 0; i < k; i++) {
            swap(nums[0], nums[heap_size - 1]);
            heap_size--;
            max_heapify(nums, 0);
        }
        return nums[heap_size];
    }
};

// quick select, O(n) is the average time complexity. In the worst case, the recursion may become T(n) = T(n - 1) + O(n) and the complexity will be O(n^2).
// Space O(1)
// https://discuss.leetcode.com/topic/15256/4-c-solutions-using-partition-max-heap-priority_queue-and-multiset-respectively
class Solution {
public:
    int partition(vector<int>& nums, int left, int right) {
        int pivot = nums[left];
        int l = left + 1;
        int r = right;
        while(l <= r) {
            if(nums[l] < pivot && nums[r] > pivot) {
                swap(nums[l++], nums[r--]);
            }
            if(nums[l] >= pivot) l++;
            if(nums[r] <= pivot) r--;
        }
        swap(nums[left], nums[r]);
        return r;
    }

    int findKthLargest(vector<int>& nums, int k) {
        int left = 0;
        int right = nums.size() - 1;
        while(true) {
            int pos = partition(nums, left, right);
            if(pos == k - 1) return nums[pos];
            if(pos > k - 1) right = pos - 1;
            else left = pos + 1;
        }
    }
};
