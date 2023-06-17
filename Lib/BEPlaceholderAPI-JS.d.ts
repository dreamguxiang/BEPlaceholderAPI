export class PAPI {
  constructor() {}

  /**
   * 注册玩家变量
   * @param func 关联函数
   * @param pluginName 插件名称
   * @param placeholderName 变量名称
   */
  static registerPlayerPlaceholder(
    func: (xuid: string, params: any) => string,
    pluginName: string,
    placeholderName: string
  );

  /**
   * 注册服务器变量
   * @param func 关联函数
   * @param pluginName 插件名称
   * @param placeholderName 变量名称
   */
  static registerServerPlaceholder(
    func: (params: any) => string,
    pluginName: string,
    placeholderName: string
  );

  /**
   * 注册静态变量
   * @param func 关联函数
   * @param pluginName 插件名称
   * @param placeholderName 变量名称
   */
  static registerStaticPlaceholder(
    func: () => string,
    pluginName: string,
    placeholderName: string,
    updateInterval: number
  );

  /**
   * 获得变量值（不包括玩家变量）
   * @param key 变量名称
   */
  static getValue(key: string);

  /**
   * 获得变量值
   * @param key 变量名称
   * @param xuid 玩家 XUID
   */
  static getValueByPlayer(key: string, xuid: string);

  /**
   * 获取包含多个变量的字符串
   * @param str 待替换字符串
   * @param xuid 玩家 XUID
   */
  static translateString(str: string, xuid: string);

  /**
   * 取消注册变量
   * @param placeholderName 变量名
   */
  static unRegisterPlaceholder(placeholderName: string);
}
