public class interface_test {
  public static void main(String argv[]) {
    System.loadLibrary("kodijava");

    addon_properties props = new addon_properties();
    props.setId("demo_java_addon");
    props.setType("xbmc.addon.executable");
    props.setVersion("0.0.1");
    props.setName("Demo Java add-on");
    props.setLicense("GPL2");
    props.setSummary("");
    props.setDescription("Hello World");
    props.setPath("");
    props.setLibname("");
    props.setAuthor("");
    props.setSource("");
    props.setIcon("");
    props.setDisclaimer("");
    props.setChangelog("");
    props.setFanart("");
    props.setIndependent(false);

    kodi.Init(props);

    kodi.Log(addonLog.LOG_DEBUG, "Hello LOG_DEBUG");
    kodi.Log(addonLog.LOG_INFO, "Hello LOG_INFO");
    kodi.Log(addonLog.LOG_NOTICE, "Hello LOG_NOTICE");
    kodi.Log(addonLog.LOG_WARNING, "Hello LOG_WARNING");
    kodi.Log(addonLog.LOG_ERROR, "Hello LOG_ERROR");
    kodi.Log(addonLog.LOG_SEVERE, "Hello LOG_SEVERE");
    kodi.Log(addonLog.LOG_FATAL, "Hello LOG_FATAL");
    kodi.Log(addonLog.LOG_DEBUG, "Hello formatted entry: " + "tata " + 123 + " " +  0.10101);
  }
}
