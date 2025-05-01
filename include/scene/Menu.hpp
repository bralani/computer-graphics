#ifndef MENU_HPP
#define MENU_HPP

#include <string>
#include <unordered_map>
#include <vector>
#include <chrono>

enum class MenuItem
{
    Empty,
    ZeroItems,
    OneItem,
    TwoItems,
    ThreeItems,
    FourItems,
    BoatBroken,
    PressF,
    PressV,
};

class Menu
{
    struct ScheduledPop {
        double expirationTime;
        int row;
    };

public:
    std::string getMenuItemString(MenuItem item)
    {
        return mapTexts.at(item);
    }

    void setMenuItem(MenuItem item, int row)
    {
        switch (row)
        {
            case 0:
                firstRow = item;
                break;
            case 1:
                secondRow = item;
                break;
            case 2:
                thirdRow = item;
                break;
            case 3:
                fourthRow = item;
                break;
            default:
                break;
        }

        updatePipeline = true;
    }

    void pushMenuItem(MenuItem item, double seconds)
    {
        int targetRow = -1;
        
        if (firstRow == MenuItem::Empty)
        {
            firstRow = item;
            targetRow = 0;
        }
        else if (secondRow == MenuItem::Empty)
        {
            secondRow = item;
            targetRow = 1;
        }
        else if (thirdRow == MenuItem::Empty)
        {
            thirdRow = item;
            targetRow = 2;
        }
        else if (fourthRow == MenuItem::Empty)
        {
            fourthRow = item;
            targetRow = 3;
        }

        if(targetRow == -1) return;

        updatePipeline = true;

        auto now = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
        scheduledPops.push_back({duration + seconds * 1000.0, targetRow});
    }

    void update() {
        auto now = std::chrono::high_resolution_clock::now();
        auto currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();

        auto it = scheduledPops.begin();
        while(it != scheduledPops.end()) {
            if(it->expirationTime <= currentTime) {
                switch(it->row) {
                    case 0: firstRow = MenuItem::Empty; break;
                    case 1: secondRow = MenuItem::Empty; break;
                    case 2: thirdRow = MenuItem::Empty; break;
                    case 3: fourthRow = MenuItem::Empty; break;
                }
                it = scheduledPops.erase(it);
                updatePipeline = true;
            }
            else {
                ++it;
            }
        }
    }

    int getMenuItemIndex(MenuItem item) const
    {
        return static_cast<int>(item);
    }

    int getMenuItemCount() const
    {
        return mapTexts.size();
    }

    int getMenuIndex() const
    {
        int i = static_cast<int>(firstRow);
        int j = static_cast<int>(secondRow);
        int k = static_cast<int>(thirdRow);
        int l = static_cast<int>(fourthRow);
        int num_items = getMenuItemCount();

        int combo = i * num_items * num_items * num_items +
                    j * num_items * num_items +
                    k * num_items +
                    l;

        return combo;
    }

    void setUpdatePipeline(bool update) {
        updatePipeline = update;
    }
    bool getUpdatePipeline() const {
        return updatePipeline;
    }

    Menu() = default;
    ~Menu() = default;

private:
    std::unordered_map<MenuItem, std::string> mapTexts = {
        {MenuItem::Empty, ""},
        {MenuItem::ZeroItems, "0/4 items found"},
        {MenuItem::OneItem, "1/4 items found"},
        {MenuItem::TwoItems, "2/4 items found"},
        {MenuItem::ThreeItems, "3/4 items found"},
        {MenuItem::FourItems, "You found all items! Now you can go back to the boat!"},
        {MenuItem::BoatBroken, "The boat is broken! Please find a way to fix it!"},
        {MenuItem::PressF, "Press F to pick up the item"},
        {MenuItem::PressV, "Press V to change camera"},
    };

    MenuItem firstRow = MenuItem::ZeroItems;
    MenuItem secondRow = MenuItem::Empty;
    MenuItem thirdRow = MenuItem::Empty;
    MenuItem fourthRow = MenuItem::Empty;

    std::vector<ScheduledPop> scheduledPops;
    bool updatePipeline = false;
};

#endif // MENU_HPP