#pragma once
#include <iostream>

/**
 * @struct Ticket
 * @brief Represents a travel ticket with source, destination, carrier, and fare information.
 * 
 * @var Ticket::source
 * The source location of the ticket. Default is "NO_SOURCE".
 * 
 * @var Ticket::destination
 * The destination location of the ticket. Default is "NO_DESTINATION".
 * 
 * @var Ticket::carrier
 * The carrier providing the service. Default is "NO_CARRIER".
 * 
 * @var Ticket::fare
 * The fare cost of the ticket. Default is 0.
 */
struct Ticket {
    std::string_view origin {"NO_SOURCE"};
    std::string_view destination {"NO_DESTINATION"};
    std::string_view carrier {"NO_CARRIER"};
    size_t fare {0};
};

/**
 * @class AirTicket
 * @brief A class to represent an air ticket.
 *
 * The AirTicket class manages the lifecycle of a Ticket object, including
 * creation, copying, assignment, and destruction. It ensures proper memory
 * management by implementing the Rule of Three.
 */
 
/**
 * @brief Default constructor.
 *
 * Initializes an AirTicket object with a null Ticket pointer.
 */
 
/**
 * @brief Parameterized constructor.
 * 
 * @param ticket A reference to a Ticket object to initialize the AirTicket.
 *
 * Creates a new AirTicket object by allocating memory for a new Ticket
 * and copying the provided Ticket.
 */
 
/**
 * @brief Copy constructor.
 * 
 * @param src A reference to the AirTicket object to copy from.
 *
 * Creates a new AirTicket object by deep copying the Ticket from the source
 * AirTicket object.
 */
 
/**
 * @brief Copy assignment operator.
 * 
 * @param src A reference to the AirTicket object to assign from.
 * @return A reference to the assigned AirTicket object.
 *
 * Assigns the content of the source AirTicket object to the current object,
 * ensuring proper memory management by releasing previously allocated memory
 * and deep copying the Ticket from the source.
 */

/**
 * @brief Move constructor.
 * 
 * @param src A reference to the AirTicket object to move from.
 *
 * Creates a new AirTicket object by moving the Ticket from the source
 * AirTicket object.
 */

/**
 * @brief Move assignment operator.
 * 
 * @param src A reference to the AirTicket object to move from.
 * 
 * Assigns the content of the source AirTicket object to the current object,
 * ensuring proper memory management by releasing previously allocated memory
 * and moving the Ticket from the source.
 */
 
/**
 * @brief Destructor.
 *
 * Releases the memory allocated for the Ticket object and performs cleanup.
 */
 
/**
 * @brief Prints information about the Ticket.
 *
 * Outputs the details of the Ticket, including the source, destination, and fare.
 */
class AirTicket {
public:
    // default constructor
    AirTicket() : m_ticket(nullptr) {}
    // constructor
    AirTicket(const Ticket& ticket) {
        m_ticket = new Ticket(ticket);
        std::cout << "Creating a new Air Ticket at: " << this << std::endl;
    }

    // copy constructor
    AirTicket(const AirTicket& src) {
        // check for nullness to avoid nullptr dereferencing
        if(src.m_ticket) {
            m_ticket = new Ticket(*src.m_ticket);
        } else {
            m_ticket = nullptr;
        }
        std::cout << "Copying Air Ticket from: " << &src << " to: " << this << std::endl;
    }

    // copy assignment operator
    AirTicket& operator=(const AirTicket& src) {
        if(this != &src) {
            // release memory before allocating new memory for m_ticket
            delete m_ticket;
            if(src.m_ticket) {
                m_ticket = new Ticket(*src.m_ticket);
            } else {
                m_ticket = nullptr;
            }
            std::cout << "Assigning Air Ticket from: " << &src << " to: " << this << std::endl;
        } else {
            std::cout << "WARN: Trying to assign the same element." << std::endl;
        }
        return *this;
    }

    // Move constructor
    AirTicket(AirTicket&& src) noexcept : m_ticket(src.m_ticket) {
        src.m_ticket = nullptr;
        std::cout << "Moving Air Ticket from: " << &src << " to: " << this << std::endl;
    }

    // Move operator
    AirTicket& operator=(AirTicket&& src) noexcept {
        if(this != &src) {
            m_ticket = std::move(src.m_ticket);
            src.m_ticket = nullptr;
            std::cout << "Moving Air Ticket using operator from: " << &src << " to: " << this << std::endl;
        } else {
            std::cout << "WARN: Trying to move the same element." << std::endl;
        }
        return *this;
    }

    // Destructor
    ~AirTicket() {
        std::cout << "Deleting Air Ticket at: " << this << std::endl;
        delete m_ticket;
    }

    // print information about the Ticket
    void print() const {
        if (m_ticket) {
            std::cout << "--------------Ticket--------------\n";
            std::cout << "TICKET TYPE: AIR\n";
            std::cout << "FROM: " << m_ticket->origin << std::endl;
            std::cout << "TO: " << m_ticket->destination << std::endl;
            std::cout << "FARE: " << m_ticket->fare << std::endl;
            std::cout << "----------------------------------\n\n";
        } else {
            std::cout << "No ticket information available.\n";
        }
    }
private:
    Ticket* m_ticket;
};

int main() {
    Ticket justTicket {"Almaty", "London", "Air Astana", 1000};
    AirTicket airT1(justTicket);
    AirTicket airT2;
    airT2 = airT1;
    AirTicket airT3(airT2);
    AirTicket airT4(justTicket);
    airT4 = airT1;
    AirTicket airT5;
    airT5 = airT5;

    // move tests
    AirTicket airT6 = std::move(airT1);
    AirTicket airT7;
    airT7 = std::move(airT6);
    return 0;
}