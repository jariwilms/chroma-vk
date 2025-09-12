//export module vx.command_pool;
//
//import std;
//import vx;
//import vx.logical_device;
//
//export namespace vx
//{
//    class command_pool
//    {
//    public:
//        command_pool(vx::logical_device logical_device)
//        {
//            const auto command_pool_create_info = vx::command_pool_create_info
//            {
//                .flags              = vx::command_pool_create_flags_e::reset_command_buffer, 
//                .queue_family_index = logical_device.queue_index()                         , 
//            };
//
//            command_pool_ = vx::create_command_pool(logical_device, command_pool_create_info);
//        }
//
//    private:
//        vx::command_pool_t command_pool_;
//    };
//}
