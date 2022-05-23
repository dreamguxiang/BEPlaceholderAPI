using LLNET.LL;
using LLNET.Logger;
using LLNET.Event;
using BEPlaceholderAPI;

namespace PluginMain
{
    public class Plugin
    {
        internal static readonly Logger logger = new("PluginName");
        
        
        public static string TestNET()
        {
            return "hi .NET";
        }
        
        public static void OnPostInit()
        {
            LLAPI.RegisterPlugin("PluginName11", "Introduction", new(1, 0, 0));
            events();
        }

        public static void events()
        {
            ServerStartedEvent.Subscribe(ev =>
            {
                
                PAPI.registerServerPlaceholder(TestNET, "BEPlaceholderAPI_NET", "server_testnet");
                return true;
            });
            
        }
    }
}