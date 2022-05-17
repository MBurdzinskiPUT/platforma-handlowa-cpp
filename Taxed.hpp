#ifndef TAXED_HPP
#define TAXED_HPP

class Taxed { // Interface

    protected:

    static constexpr float salesTax = 0.23;

    virtual float calculateTax () = 0;
    
};

#endif