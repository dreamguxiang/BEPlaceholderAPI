using LLNET.RemoteCall;
namespace BEPlaceholderAPI
{
    public class PAPI
    {
   
        static public void registerServerPlaceholder(Func<string> func, string PluginName, string PAPIName)
        {
            RemoteCallAPI.ExportFunc(PluginName, func.Method.Name, (args) =>
            {
                return func();
            });
           var funcs = RemoteCallAPI.ImportFunc("BEPlaceholderAPI", "registerServerPlaceholder");
            funcs(new(){ PluginName , func.Method.Name, PAPIName });
        }

        static public void registerserverplaceholder(Func<Dictionary<string, string>, string> func, string pluginname, string papiname)
        {
            RemoteCallAPI.ExportFunc(pluginname, func.Method.Name, (args) =>
            {
                return func(args[0]);
            });
            var funcs = RemoteCallAPI.ImportFunc("beplaceholderapi", "registerserverplaceholder");
            funcs(new() { pluginname, func.Method.Name, papiname });
        }

        static public void registerPlayerPlaceholder(Func<MC.Player,string> func, string PluginName, string PAPIName)
        {
            RemoteCallAPI.ExportFunc(PluginName, func.Method.Name, (args) =>
            {
                return func(MC.Level.GetPlayer(args[0]));
            });
            var funcs = RemoteCallAPI.ImportFunc("BEPlaceholderAPI", "registerPlayerPlaceholder");
            funcs(new() { PluginName, func.Method.Name, PAPIName });
        }

        static public void registerPlayerPlaceholder(Func<MC.Player, Dictionary<string, string>, string> func, string PluginName, string PAPIName)
        {
            RemoteCallAPI.ExportFunc(PluginName, func.Method.Name, (args) =>
            {
                return func(MC.Level.GetPlayer(args[0]),args[1]);
            });
            var funcs = RemoteCallAPI.ImportFunc("BEPlaceholderAPI", "registerPlayerPlaceholder");
            funcs(new() { PluginName, func.Method.Name, PAPIName });
        }


        static public void registerStaticPlaceholder(Func<string> func, string PluginName, string PAPIName,int num)
        {
            RemoteCallAPI.ExportFunc(PluginName, func.Method.Name, (args) =>
            {
                return func();
            });
            var funcs = RemoteCallAPI.ImportFunc("BEPlaceholderAPI", "registerStaticPlaceholder");
            funcs(new() { PluginName, func.Method.Name, PAPIName , num });
        }

        static public void registerStaticPlaceholder(Func<string> func, string PluginName, string PAPIName)
        {
            RemoteCallAPI.ExportFunc(PluginName, func.Method.Name, (args) =>
            {
                return func();
            });
            var funcs = RemoteCallAPI.ImportFunc("BEPlaceholderAPI", "registerStaticPlaceholder");
            funcs(new() { PluginName, func.Method.Name, PAPIName, -1 });
        }

        static public string GetValue(string a1)
        {
            var funcs = RemoteCallAPI.ImportFunc("BEPlaceholderAPI", "GetValue");
            var outs = funcs(new() { a1 });
            return outs;
        }

        static public string GetValue(string a1,MC.Player sp)
        {
            var funcs = RemoteCallAPI.ImportFunc("BEPlaceholderAPI", "GetValueWithPlayer");
            var outs = funcs(new() { a1,sp.RealName});
            return outs;
        }

        static public string translateString(string a1, MC.Player sp)
        {
            var funcs = RemoteCallAPI.ImportFunc("BEPlaceholderAPI", "translateString");
            var outs = funcs(new() { a1, sp.RealName });
            return outs;
        }

        static public string unRegisterPlaceholder(string a1)
        {
            var funcs = RemoteCallAPI.ImportFunc("BEPlaceholderAPI", "unRegisterPlaceholder");
            var outs = funcs(new() { a1 });
            return outs;
        }
    }
}