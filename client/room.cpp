#include "room.hpp"

        room::room() :
            room_id(0),
            zone_id(0),
            room_name("default"),
            room_description("default"),
            room_exits(room::default_exits())
            // Placeholder: Mobiles
            // Placeholder: Items
        {

        }

        room::room(int rnum, int znum, std::string rname, std::string rdesc,  std::array<exit,6> rexits) :
            room_id(rnum),
            zone_id(znum),
            room_name(rname),
            room_description(rdesc),
            room_exits(rexits)
            // Placeholder: Mobiles
            // Placeholder: Items
        {

        }

        std::ostream& operator<<(std::ostream& os, const room& r1)
        {
            std::string exits = "[";
            for(int y = 0; y < r1.room_exits.size(); y++)
            {
                switch (y)
                {
                case 0:
                    if (r1.room_exits[y].room_id > 0) { exits += " n"; }
                    break;

                case 1:
                    if (r1.room_exits[y].room_id > 0) { exits += " s"; }
                    break;

                case 2:
                    if (r1.room_exits[y].room_id > 0) { exits += " e"; }
                    break;

                case 3:
                    if (r1.room_exits[y].room_id > 0) { exits += " w"; }
                    break;

                case 4:
                    if (r1.room_exits[y].room_id > 0) { exits += " u"; }
                    break;

                case 5:
                    if (r1.room_exits[y].room_id > 0) { exits += " d"; }
                    break;
                
                default:
                    break;
                }
            }

            exits += " ]";

            if(exits == "[ ]")
            {
                os << r1.room_name << "\n\n"
                   << r1.room_description << "\n";
            }
            else
            {
                os << r1.room_name << "\n\n"
                   << r1.room_description << "\n"
                   << exits << "\n";
            }

            return os;
        }

        void room::set_room_id(int rnum)
        {
            room_id = rnum;
        }

        void room::set_zone_id(int znum)
        {
            zone_id = znum;
        }

        void room::set_room_name(std::string rname)
        {
            room_name = rname;
        }

        void room::set_room_desc(std::string rdesc)
        {
            room_description = rdesc;
        }

        void room::set_room_exits(std::array<exit,6> rexits)
        {
            room_exits = rexits;
        }

        void room::set_room_exits(int exit_zone_n, int exit_room_n,
                            int exit_zone_s, int exit_room_s,
                            int exit_zone_e, int exit_room_e,
                            int exit_zone_w, int exit_room_w,
                            int exit_zone_u, int exit_room_u,
                            int exit_zone_d, int exit_room_d)
        {
            exit n,s,e,w,u,d;
            n.zone_id = exit_zone_n;    n.room_id = exit_room_n;
            s.zone_id = exit_zone_s;    s.room_id = exit_room_s;
            e.zone_id = exit_zone_e;    e.room_id = exit_room_e;
            w.zone_id = exit_zone_w;    w.room_id = exit_room_w;
            u.zone_id = exit_zone_u;    u.room_id = exit_room_u;
            d.zone_id = exit_zone_d;    d.room_id = exit_room_d;

            room_exits[0] = n;
            room_exits[1] = s;
            room_exits[2] = e;
            room_exits[3] = w;
            room_exits[4] = u;
            room_exits[5] = d;
        }

        int room::get_room_id()
        {
            return room_id;
        }

        int room::get_zone_id()
        {
            return zone_id;
        }

        std::string room::get_room_name()
        {
            return room_name;
        }

        std::string room::get_room_desc()
        {
            return room_description;
        }

        std::array<room::exit,6> room::get_room_exits()
        {
            return room_exits;
        }

        std::array<room::exit,6> room::default_exits()
        {
            std::array<exit, 6> e;
            exit re;
            re.room_id = 0;
            re.zone_id = 0;
            for(int i = 0; i < e.size(); i ++)
            {
                e[i] = re;
            }

            return e;
        }