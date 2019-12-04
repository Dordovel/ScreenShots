#include <vector>
#include <string>

struct WindowObject;

class IFindWindow
{
    public:
        virtual std::vector<WindowObject> search_window(std::string searchWindowName = "") = 0;
        virtual ~IFindWindow() = default;
};
