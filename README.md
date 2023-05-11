# PyoPlug for MacOS X 13 / Python 3.11 (Maybe work on Windows 10/11)

![IMG](https://github.com/crackerjacques/PyoPlug_Python311_VST3/blob/master/pyoplugvst3.png?raw=true)

There was a plugin called pyoplug that looked like a lot of fun, so I rewrote it to work with Python 3.11 and MacOS13.
As a byproduct, a VST3 plugin was created. (Heck, it didn't even work with Reaper 6.79.)

```
git clone https://github.com/crackerjacques/PyoPlug.git
```

and don't forget

```
brew install python@3.11
```

```
pip install pyo
```

and open with JUCE, Export for Xcode, configure then build.


# 

It is a modification to the extent that methods that are not used now are rewritten with VST3 SDK and JUCE7 methods. __VST2 works stably, but VST3 seems to be very host selective and unstable.__

plugin hosts in my home...

Nuendo

PluginDoctor

Adobe Autidion

Bidule

KushView Element

I was able to confirm that the plugin works with
(It is possible to make it work by bridging it with Bidule and KushView.)

I definitely need to review and rewrite the source code for the VST3 SDK a bit more.





--------↓ORIGINAL ARTICLES------

# PyoPlug  


### Description

PyoPlug is a framework to embed the python module for digital signal processing "Pyo" into different types of audio plugins.

**Supported Wrapper**  

- VST
- Audio Unit
  
--- 

### Installation 

_Make sure to have Pyo version 0.6.8 or later installed:_

- _Installer: <http://code.google.com/p/pyo/downloads/list>_

- _Sources (If you want the latest build): <http://code.google.com/p/pyo/source/checkout>_ 

 
**Mac OS X :**  

To install the plugins, compile the Xcode project or copy the compiled ones from the "Builds/MacOSX/" directory into your audio plugins folders:  

- VST : ~/Library/Audio/Plug-Ins/VST/
- Audio Unit : ~/Library/Audio/Plug-Ins/Components/

The presets are also needed to make it works. To install them, just copy the "PyoPlug" folder inside the "ScriptsPresets" folder to your Audio "Presets" folder. (This is mandatory to copy it inside the "Preset" folder of your home directory)

- ~/Library/Audio/Presets/


---    

### Documentation  
  

- PyoPlug : (Sorry, there's only a french version for now)   
	*   <https://github.com/guibarrette/PyoPlug/blob/master/Documentation/PyoPlug-DocumentationFR.md>

- Pyo :   
	* Information: <http://code.google.com/p/pyo/>  
	* Documentation: <http://www.iact.umontreal.ca/pyo/manual/>
	* Discussions: <https://groups.google.com/forum/#!forum/pyo-discuss>


---

## Warning

The scripts are loaded directly in the Python interpreter to make it possible for Pyo to run them. This allows the importation of any Python module and scripts. This is great in a way, but can be dangereous if a script that manipulates system files or makes any unwanted behavior is loaded. Therefore, in order to avoid any problems and risks to your computer, please make sure to review any script before running it. I'm not liable to any damages of any sort and distribute this software with no warranty.

  
---

<sup>Happy coding,  
 Guillaume Barrette</sup>




# Original Articles

# PyoPlug  


### Description

PyoPlug is a framework to embed the python module for digital signal processing "Pyo" into different types of audio plugins.

**Supported Wrapper**  

- VST
- Audio Unit
  
--- 

### Installation 

_Make sure to have Pyo version 0.6.8 or later installed:_

- _Installer: <http://code.google.com/p/pyo/downloads/list>_

- _Sources (If you want the latest build): <http://code.google.com/p/pyo/source/checkout>_ 

 
**Mac OS X :**  

To install the plugins, compile the Xcode project or copy the compiled ones from the "Builds/MacOSX/" directory into your audio plugins folders:  

- VST : ~/Library/Audio/Plug-Ins/VST/
- Audio Unit : ~/Library/Audio/Plug-Ins/Components/

The presets are also needed to make it works. To install them, just copy the "PyoPlug" folder inside the "ScriptsPresets" folder to your Audio "Presets" folder. (This is mandatory to copy it inside the "Preset" folder of your home directory)

- ~/Library/Audio/Presets/


---    

### Documentation  
  

- PyoPlug : (Sorry, there's only a french version for now)   
	*   <https://github.com/guibarrette/PyoPlug/blob/master/Documentation/PyoPlug-DocumentationFR.md>

- Pyo :   
	* Information: <http://code.google.com/p/pyo/>  
	* Documentation: <http://www.iact.umontreal.ca/pyo/manual/>
	* Discussions: <https://groups.google.com/forum/#!forum/pyo-discuss>


---

## Warning

The scripts are loaded directly in the Python interpreter to make it possible for Pyo to run them. This allows the importation of any Python module and scripts. This is great in a way, but can be dangereous if a script that manipulates system files or makes any unwanted behavior is loaded. Therefore, in order to avoid any problems and risks to your computer, please make sure to review any script before running it. I'm not liable to any damages of any sort and distribute this software with no warranty.

  
---

<sup>Happy coding,  
 Guillaume Barrette</sup>
