#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <vector>

class BankEvent {
    public:
        BankEvent();
        BankEvent(int, int, int, bool);
        BankEvent(const BankEvent&);

        BankEvent& operator=(const BankEvent&);
        friend bool operator<(const BankEvent&, const BankEvent&);

        void setEvent(int, int, bool);

        int getTime() const;
        int getTransactionTime() const;
        int getLineNumber() const;
        bool getIsArrivalEvent() const;
    private:
        int time;
        int transactionTime;
        int lineNumber;

        bool isArrivalEvent;
};

class BankNode {
    private:
        BankNode(int, int, bool, BankNode*);

        BankEvent data;
        BankNode* next;
        friend class BankQueue;
};

class BankQueue {
    public:
        BankQueue();
        ~BankQueue();

        bool isEmpty() const;
        bool enqueue(const BankEvent& newEvent);
        bool dequeue();
        int length() const;

        BankEvent peekFront() const;
    private:
        BankNode* frontPtr;
        BankNode* backPtr;
        int queueLength;
};

class BankPriorityQueue {
    public:
        BankPriorityQueue();

        bool isEmpty() const;
        bool enqueue(const BankEvent& newEvent);
        bool dequeue();

        BankEvent peekFront() const;
    private:
        std::list<BankEvent> bankList;
};

class BankSimulation {
    public:
        BankSimulation();
        void generateData(int);
        void simulateOneTeller(int);
        void simulateThreeTellers(int);
        void simulateOneLine(int);
        void processArrival(BankEvent&, BankPriorityQueue&, BankQueue&, int);
        void processDeparture(BankEvent&, BankPriorityQueue&, BankQueue&);
        void chooseArrivalLine(BankQueue&, BankQueue&, BankQueue&, BankPriorityQueue&, BankEvent&);
        void chooseDepartureLine(BankQueue&, BankQueue&, BankQueue&, BankPriorityQueue&, BankEvent&);
        void chooseTellerArrival(BankEvent&, BankPriorityQueue&, BankQueue&);
        bool isTellerAvailable(int);
        void maxWaitInLine(int);
        void maxLineLength(int);
        void reset();
        void generateResultsTable();
    private:
        bool tellerOneAvailable;
        bool tellerTwoAvailable;
        bool tellerThreeAvailable;
        int currentTime;
        int totalProcessed;
        int maxWaitTime;
        int maxLengthOfLine;
        double totalWaitTime;
        double avgLengthOfLine;

        std::vector<double> oneTellerResults;
        std::vector<double> threeTellerResults;
        std::vector<double> oneLineResults;

        std::ofstream outputFile;
};