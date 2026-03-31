// Implementation for Problem 059 - OJ 的继承与派生
#include <cstdio>
#include <cstring>
#include <cmath>

class BaseJudger {
public:
    BaseJudger(size_t time_limit, size_t memory_limit, const char *answer)
        : time_limit_(time_limit), memory_limit_(memory_limit), score_(0) {
        if (answer == nullptr) {
            answer_ = nullptr;
        } else {
            size_t len = std::strlen(answer);
            answer_ = new char[len + 1];
            std::memcpy(answer_, answer, len + 1);
        }
    }

    virtual void Submit(size_t time, size_t memory, const char *output) = 0;

    size_t GetScore() const { return score_; }

    virtual ~BaseJudger() {
        delete[] answer_;
        answer_ = nullptr;
    };

protected:
    char *answer_;
    const size_t time_limit_;
    const size_t memory_limit_;
    size_t score_;

    virtual bool CheckAnswer(const char *output) const {
        // the output must equal to the answer
        if (answer_ == nullptr && output == nullptr) return true;
        if (answer_ == nullptr || output == nullptr) return false;
        return std::strcmp(answer_, output) == 0;
    }
};

class ICPCJudger : public BaseJudger {
public:
    ICPCJudger(size_t time_limit, size_t memory_limit, const char *answer)
        : BaseJudger(time_limit, memory_limit, answer) {}

    void Submit(size_t time, size_t memory, const char *output) override {
        size_t curr = 0;
        if (time <= time_limit_ && memory <= memory_limit_ && CheckAnswer(output)) {
            curr = 100;
        }
        if (curr > score_) score_ = curr;
    }
};

class OIJudger : public BaseJudger {
public:
    OIJudger(size_t time_limit, size_t memory_limit, const char *answer)
        : BaseJudger(time_limit, memory_limit, answer), submitted_(false) {}

    void Submit(size_t time, size_t memory, const char *output) override {
        if (submitted_) {
            // Multiple submissions -> zero score
            score_ = 0;
            return;
        }
        size_t curr = 0;
        if (time <= time_limit_ && memory <= memory_limit_ && CheckAnswer(output)) {
            curr = 100;
        }
        score_ = curr;
        submitted_ = true;
    }

protected:
    bool CheckAnswer(const char *output) const override {
        // Compare answer_ and output ignoring trailing spaces at the end of each line
        if (answer_ == nullptr && output == nullptr) return true;
        if (answer_ == nullptr || output == nullptr) return false;
        const char *a = answer_;
        const char *b = output;
        while (true) {
            // Find end of line for a
            const char *ea = a;
            while (*ea != '\0' && *ea != '\n') ++ea;
            // Find end of line for b
            const char *eb = b;
            while (*eb != '\0' && *eb != '\n') ++eb;

            // Trim trailing spaces on the line (only spaces, not tabs)
            const char *ta = ea;
            while (ta > a && *(ta - 1) == ' ') --ta;
            const char *tb = eb;
            while (tb > b && *(tb - 1) == ' ') --tb;

            size_t la = static_cast<size_t>(ta - a);
            size_t lb = static_cast<size_t>(tb - b);
            if (la != lb) return false;
            if (la > 0 && std::strncmp(a, b, la) != 0) return false;

            // If both reached string end, they are equal
            bool enda = (*ea == '\0');
            bool endb = (*eb == '\0');
            if (enda || endb) {
                return enda && endb; // both must end together
            }

            // Both have '\n', step to next line
            a = ea + 1;
            b = eb + 1;
        }
    }

private:
    bool submitted_;
};

class SpacialJudger : public BaseJudger {
public:
    SpacialJudger(size_t time_limit, size_t memory_limit,
                  size_t full_score_time, size_t full_score_memory,
                  const char *answer)
        : BaseJudger(time_limit, memory_limit, answer),
          full_score_time_(full_score_time),
          full_score_memory_(full_score_memory) {}

    void Submit(size_t time, size_t memory, const char *output) override {
        size_t curr = 0;
        if (time <= time_limit_ && memory <= memory_limit_ && CheckAnswer(output)) {
            int time_score = 0;
            if (time <= full_score_time_) {
                time_score = 100;
            } else if (time >= time_limit_) {
                time_score = 0;
            } else {
                // Linear from 100 at full_score_time_ to 0 at time_limit_
                size_t denom = time_limit_ - full_score_time_;
                size_t numer = time_limit_ - time;
                time_score = static_cast<int>((100ULL * numer) / denom);
            }

            int memory_score = 0;
            if (memory <= full_score_memory_) {
                memory_score = 100;
            } else if (memory >= memory_limit_) {
                memory_score = 0;
            } else {
                size_t denom = memory_limit_ - full_score_memory_;
                size_t numer = memory_limit_ - memory;
                memory_score = static_cast<int>((100ULL * numer) / denom);
            }

            curr = static_cast<size_t>((time_score * memory_score) / 100);
        }
        if (curr > score_) score_ = curr;
    }

private:
    size_t full_score_time_;
    size_t full_score_memory_;
};

