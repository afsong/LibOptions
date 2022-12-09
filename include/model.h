#ifndef LIBOPTIONS_MODEL_H
#define LIBOPTIONS_MODEL_H

namespace LibOptions {

class Model {
public:
    virtual double calc_value() = 0;
};

} // namespace LibOptions
#endif