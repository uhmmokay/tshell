#include <cstdint>
#include <iostream>
#include <string>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>


class Command{

    private:
        std::string command;
        std::int16_t status {2000};
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
                std::cout << "< " << user << " > -> ";
                
                if (this->status)
                {
                    std::cout << "{" << this->status << "} ";
                }
                std::cout << "$ " << std::flush;

                char* input = readline("");

                std::string whattodo;
                if (input == nullptr) {
                    std::cout << "\n[Session ended]" << std::endl;
                    break;
                }
                whattodo = input;
                free (input);
                if (whattodo == "exitplease") {break;} else if (whattodo.empty()) {continue;} else {
                    add_history(whattodo.c_str()); 
                    this->status = this->exec(whattodo);
                }
            }
        }
};

int main()
{
    std::cout << "Welcome to TShell! A Shell written in C++. Enjoy your stay here.\n";
    Shell shell;
    shell.start();
    return 0;
}

