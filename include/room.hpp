#include <iostream>
#include <string>
#include <vector>
#include <array>

class room
{
    private:

        int room_id;
        int zone_id;
        std::string room_name;
        std::string room_description;
        
        struct exit
        { int zone_id; int room_id; };
        
        std::array<exit,6> room_exits;

    public:

        room();

        room(int rnum, int znum, std::string rname, std::string rdesc, std::array<exit,6> rexits);

        friend std::ostream& operator<<(std::ostream& os, const room& r1);

        void set_room_id(int rnum);

        void set_zone_id(int znum);

        void set_room_name(std::string rname);

        void set_room_desc(std::string rdesc);

        void set_room_exits(std::array<exit,6> rexits);

        void set_room_exits(int exit_zone_n, int exit_room_n,
                            int exit_zone_s, int exit_room_s,
                            int exit_zone_e, int exit_room_e,
                            int exit_zone_w, int exit_room_w,
                            int exit_zone_u, int exit_room_u,
                            int exit_zone_d, int exit_room_d);

        int get_room_id();

        int get_zone_id();

        std::string get_room_name();

        std::string get_room_desc();

        std::array<exit,6> get_room_exits();

        std::array<exit,6> default_exits();

};