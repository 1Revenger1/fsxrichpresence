# fsxrichpresence

FSXRichPresence is a dll addon for FSX/P3D which sends information to your discord client to enhance the game status, as shown below.

![Alt text](documentation/example.png?raw=true "Title")

# How To Install
1) Download the zip by going to the top right green button "Clone or Download", and download the zip.
2) Next, you'll want to drag the folder which applies to your sim to the root directory for that sim.
  For example, FSX:SE's root directory normally is "C:\Program Files(x86)\Steam\steamapps\common\FSX"

![Alt text](documentation/directoryPlacement.png?raw=true "dir")

3) Next, you will need to go to your dll.xml, which is in "%appData%\Roaming\Microsoft\FSX" for FSX users, or "%appData%\Roaming\Lockheed Martin\prepar3d\". Once you open it, you need to add the dll to the file. You need to add the entry right after your last dll, if you have any. It should be right above the line that reads "</SimBase.Document>"

If you have FSX, the entry should look like:
```
  <Launch.Addon>
    <Name>FSXRpc</Name>
    <Disabled>False</Disabled>
    <Path>FSXRpc\FSXRichPresence.dll</Path>
  </Launch.Addon>
```
For P3D v3 and below:
```
    <Launch.Addon>
      <Name>P3DRpc</Name>
      <Disabled>False</Disabled>
      <Path>P3DRpc\FSXRichPresence.dll</Path>
    </Launch.Addon>
``` 
For P3D V4:
```
    <Launch.Addon>
      <Name>P3DRpc</Name>
      <Disabled>False</Disabled>
      <Path>P3DRpc_4\FSXRichPresence.dll</Path>
    </Launch.Addon>
``` 
For both sims, the entry should be placed as such:

![Alt text](documentation/dll.png?raw=true "dll")
