#include <cstdint>
#include <iostream>
#include <readline/rlstdc.h>
#include <string>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <csignal>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define BLACK   "\033[30m"
#define PINK    "\033[35m"
#define PURPLE  "\033[1;35m"    

namespace System {
    void changeColor (std::int16_t& color)
    {
                switch (color)
                {
                    case 0:
                    {
                        std::cout << RED;
                        break;
                    }
                    case 1:
                    {
                        std::cout << GREEN;
                        break;
                    }
                    case 2:
                    {
                        std::cout << YELLOW;
                        break;
                    }
                    case 3:
                    {
                        std::cout << BLUE;
                        break;
                    }
                    case 4:
                    {
                        std::cout << PINK;
                        break;
                    }
                    case 5:
                    {
                        std::cout << PURPLE;
                        break;
                    }
                    case 6:
                    {
                        std::cout << BLACK;
                        break;
                    }
                    case 7:
                    {
                        std::cout << RESET;
                        break;
                    }
                    default:
                    {
                        std::cout << "===========";
                        std::cout << "\n\nError. Invalid color\n\n";
                        std::cout << "===========";
                        break;
                    }
                }
    }
}



class Command{

    private:
        std::string command;
        std::int16_t status {666};
    public:
        explicit Command (std::string* n_command)
            :command(std::move(*n_command))
            {}
        
        void start ()
            {
                status = (std::system(command.c_str()));
            }
        
        const std::int16_t getStatus () {return this->status;}
};

class Shell{

    private:
        std::string user;
        std::int16_t status {0};
        std::int16_t color {4};
    
    public:
        Shell (std::string n_user = getenv("USER") ? getenv("USER") : "")
            : user(std::move(n_user))
        {
        }

        std::int16_t exec (const std::string exec)
        {

            if (exec.rfind("cd ", 0) == 0 || exec == "cd") {
                std::string path = (exec == "cd") ? (getenv("HOME") ? getenv("HOME") : ".") : exec.substr(3);
                return chdir(path.c_str()) == 0 ? 0 : 1;
            }

            std::string* PExec = new std::string {exec};
            Command* execusion = new Command {PExec};
            execusion->start();
            std::int16_t status = execusion->getStatus();
            delete execusion;
            delete PExec;
            return status;
        }

        void start ()
        {
            while (true)
            {
                System::changeColor(this->color);
                std::cout << "< " << user << " > -> ";
                
                if (this->status)
                {
                    std::cout << "{" << this->status << "} ";
                }
                std::cout << "$ ";

                char* input = readline("");

                std::string whattodo;
                if (input == nullptr) {
                    break;
                }
                whattodo = input;
                free (input);
                if (whattodo == "exitplease") {break;} else if (whattodo.empty()) {continue;} else if (whattodo == "TS_ChangeColor")
                {
                    std::cout << "Choose number (0-3)\n0 - RED\n1 - GREEN\n2 - YELLOW\n3 - BLUE\n\n4 - RESET\n\nChoice >> $ ";
                    std::cin >> this->color;
                    add_history(whattodo.c_str()); 
                    continue;
                } else {
                    add_history(whattodo.c_str()); 
                    this->status = this->exec(whattodo);
                }
            }
        }
        void changeColorId (int16_t* id) {this->color = *id; delete id;}
};

int main()
{
    std::signal(SIGINT, SIG_IGN); 
    std::cout << "Welcome to TShell! A Shell written in C++. Enjoy your stay here.\n";
    Shell shell;
    shell.start();
    shell.changeColorId(new int16_t {4});
    return 0;
}

