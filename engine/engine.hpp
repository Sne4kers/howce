#include "basic_evaluator.hpp"

class Engine {
private:
    Evaluator evaluator_;
public:
    Engine() : evaluator_(Evaluator()) {}
};