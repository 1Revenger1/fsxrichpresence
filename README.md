# fsxrichpresence

FSXRichPresence is a dll addon for FSX:SE/P3D v4.3 which sends information to your discord client to enhance the game status, as shown below.

![Alt text](documentation/example.png?raw=true "Title")

# How To Install
1) Download the zip by going to the top right green button "Clone or Download", and download the zip.
2) Next, you'll want to drag the folder which applies to your sim to the root directory for that sim.
  For example, FSX:SE's root directory normally is "C:\Program Files(x86)\Steam\steamapps\common\FSX"

![Alt text](documentation/directoryPlacement.png?raw=true "dir")

3) Next, you will need to go to your dll.xml, which is in "%appData%\Roaming\Microsoft\FSX" for FSX users, or "%appData%\Roaming\Lockheed Martin\prepar3d\". Once you open it, you need to add the dll to the file. You need to add the entry right after your last dll, if you have any. It should be right above the line that reads "</SimBase.Document>"

If you have FSX:SE, the entry should look like:
```
  <Launch.Addon>
    <Name>FSXRpc</Name>
    <Disabled>False</Disabled>
    <Path>FSXRpc_SE\FSXRichPresence.dll</Path>
  </Launch.Addon>
```
For P3D V4:
```
    <Launch.Addon>
      <Name>P3DRpc</Name>
      <Disabled>False</Disabled>
      <Path>P3DRpc_43\FSXRichPresence.dll</Path>
    </Launch.Addon>
``` 
For both sims, the entry should be placed as such:

![Alt text](documentation/dll.png?raw=true "dll")

## Last Step!
This requires the discord-rpc.dll from Discord!
Download the latest windows release from [here!](https://github.com/discordapp/discord-rpc/releases)

##### Important!
If you have P3D v3 or below, OR FSX, use the dll in the folder "win32-dynamic/bin" in the zip you just downloaded.
If you have P3D v4, use the dll in the folder "win64-dynamic/bin".

The DLL should be placed in the root directory of FSX or P3D, like shown.

![Alt text](documentation/discord.png?raw=true "discord")

# No image appears for my aircraft!
There isn't much I can do about that. I don't own very many aircraft myself, but I tried to fill in the aircrafts most used. If you want to send a picture though to be used, create an issue and I'll try to add it.

The image must be square, and have the aircraft centered pretty well and show most of the aircraft.

If I do decide to update the picture, it will not require you to redownload the dll, as all the images are stored on Discord's servers.
