const PAPI = require('./BEPlaceholderAPI/lib/BEPlaceholderAPI-JS').PAPI;

function ServerTest(){
    return "NULL"
}
function ServerTest2(obj){
    for (let key in obj){
        if(key == "<test>"){
        return obj[key]
        }
    }
    return "Fail"
}

let num = 0


function ServerTest4(obj){
    num++
    for (let key in obj){
        if(key == "<test>"){
        return obj[key] + num.toString()
        }
    }
    return "Fail";
}

mc.listen("onServerStarted", () => {
    PAPI.registerServerPlaceholder(ServerTest,"BEPlaceholderAPI_JS","server_test")
    PAPI.registerServerPlaceholder(ServerTest2,"BEPlaceholderAPI_JS","server_test_<test>")
    PAPI.registerStaticPlaceholder(ServerTest4,"BEPlaceholderAPI_JS","server_test4_<test>",50)
})

