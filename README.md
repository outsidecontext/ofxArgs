# ofxArgs
Convenient access to command line arguments for applications built using [openFrameworks](http://openframeworks.cc/) - super useful for runtime configuration.

Parses command line arguments as a variety of types (string, float, int, bool) with optional default values.

## Installation and setup
The example in the `example/` directory will give you a good idea how to set things up, but here's a step-by-step guide...

1. Clone ofxArgs into your `addons` folder.
2. In your main header file, be to sure to `#include "ofxArgs.h"`
3. Modify your `main.cpp` file to look something like this:
```
int main(int argc, char *argv[]){
	ofxArgs* args = new ofxArgs(argc, argv);

	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofSetupOpenGL(400,200, OF_WINDOW);			// <-------- setup the GL context
	
	// this kicks off the running of my app
	ofRunApp(new ofApp(args));
	delete args;
}
```

4. Make sure you have a simple constructor defined and implemented for your `ofApp` in your `ofApp.h` header file:
```
public:
    ofApp(ofxArgs* args){
        this->args = args;
    }
// your other definitions continue as normal...
```

## Passing arguments to your app
To pass in arguments, start the app from terminal or from a script like this:
* Mac OS X: `{project-path}/bin/{appname}.app/Contents/MacOS/{appname} --args -name=value -debug=true -foo=bar`
* Linux: `{project-path}/bin/appname -name=value -debug=true -foo=bar`

## Accessing and using args in your app
You can get a value passed with an argument like this:
```
string name = this->args->getString("-name");
```
Arguments come in as strings from the command line, but of course converting them to numbers can make them more useful in many scenarios. For example:
```
int portNumber = this->args->getInt("-port");
float multiplier = this->args->getFloat("-multiplier");
bool active = this->args->getBool("-active");
```

### Falling back on defaults
You might want to make certain arguments **optional**, but have a **default** value to fall back on.

In that case, just pass a default value as a second parameter to the relevant `get` function. For example:
```
int portNumber = this->args->getInt("-port", 5555);
// if app launched with -port then portNumber will get that value, otherwise portNumber will be 5555
```

This means that if you use defaults sensibly, you won't need to worry about checking if params exist before using them.

Keep in mind, though, that if you don't pass the second parameter to a `get` function, trying to access the value of an argument that has not been passed will *not* cause an error **but** the `getString` / `getInt` / `getFloat` / `getBool` function will merely return a sensible(?) default (`""` / `0` / `0.0` / `false`) instead.

### Checking flags
These things aren't always defined in a standard way, but if you want to treat some arguments as "flags" (no value), then you can either use a ternary to set your value by checking if the flag exists, e.g.:
```
string isMaster = this->contains("-master") ? "I am the master" : "I am a slave";
```
...or, use the convenient [templated](http://www.cplusplus.com/doc/oldtutorial/templates/) function `setIfFlag` with `key, valueIfSet, valueIfUnset` params, like this:
```
string isMaster = this->setIfFlag("-master", "I am the master", "I am a slave");
```

As long as the return type to be assigned matches the type of `valueIfSet` **and** `valueIfUnset`, you can do all of the following:
```
int instances = this->setIfFlag("-many", 1000, 1);
float scale = this->setIfFlag("-small", 0.1, 1.0);
```

For booleans, the simplest (and usual) case can be handled by using the version of `setIfFlag` with only one parameter:
```
bool active = this->setIfFlag("-active");
// will return true if the flag is set, false if not
```
But if you want the opposite to happen (sometimes useful), then provide the defaults explicity:
```
bool verbose = this->setIfFlag("-quiet", false, true);
// will return false if the flag IS set, true if NOT
```

### Other useful functions
* `void printArgs()`, `void printOpts()`: print out everything that was passed to the app
* `getCount`: count the number of args passed to the app

