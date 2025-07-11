class MedianFinder {
    public:
        priority_queue<double>q1;
        priority_queue<double,vector<double>,greater<>>q2;
        MedianFinder() {
            
        }
        
        void addNum(int num) {
            if(q1.size()>q2.size()){
                if(q2.empty()){
                    if(num>=q1.top())
                    q2.push(num);
                    else{
                        q2.push(q1.top());
                        q1.pop();
                        q1.push(num);
                    }
                }
                else{
                    if(num<q1.top() && num<q2.top()){
                        q2.push(q1.top());
                        q1.pop();
                        q1.push(num);
                    }
                    else{
                        q2.push(num);
                    }
                }
            }
            else{
                if(q1.empty()){
                    q1.push(num);
                }
                else{
                    if(num>q1.top() && num>q2.top()){
                        q1.push(q2.top());
                        q2.pop();
                        q2.push(num);
                    }
                    else{
                        q1.push(num);
                    }
                }
            }
        }
        
        double findMedian() {
            if(q1.size()>q2.size()){
                return q1.top();
            }
            return (q1.top()+q2.top())/2.00;
        }
    };
    