/* ------------------------------------------------------------
name: "Dunwich"
Code generated with Faust 2.87.3 (https://faust.grame.fr)
Compilation options: -a ../../faustMinimal.h -lang cpp -i -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0
------------------------------------------------------------ */

#ifndef  __mydsp_H__
#define  __mydsp_H__

#include <cmath>
#include <cstring>

/************************** BEGIN MapUI.h ******************************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ***********************************************************************/

#ifndef FAUST_MAPUI_H
#define FAUST_MAPUI_H

#include <vector>
#include <map>
#include <string>
#include <stdio.h>

/************************** BEGIN UI.h *****************************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ********************************************************************/

#ifndef __UI_H__
#define __UI_H__

/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ***************************************************************************/

#ifndef __export__
#define __export__

// Version as a global string
#define FAUSTVERSION "2.87.3"

// Version as separated [major,minor,patch] values
#define FAUSTMAJORVERSION 2
#define FAUSTMINORVERSION 87
#define FAUSTPATCHVERSION 3

// Use FAUST_API for code that is part of the external API but is also compiled in faust and libfaust
// Use LIBFAUST_API for code that is compiled in faust and libfaust

#ifdef _WIN32
    #pragma warning (disable: 4251)
    #ifdef FAUST_EXE
        #define FAUST_API
        #define LIBFAUST_API
    #elif FAUST_LIB
        #define FAUST_API __declspec(dllexport)
        #define LIBFAUST_API __declspec(dllexport)
    #else
        #define FAUST_API
        #define LIBFAUST_API 
    #endif
#else
    #ifdef FAUST_EXE
        #define FAUST_API
        #define LIBFAUST_API
    #else
        #define FAUST_API __attribute__((visibility("default")))
        #define LIBFAUST_API __attribute__((visibility("default")))
    #endif
#endif

#endif

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

/*******************************************************************************
 * UI : Faust DSP User Interface
 * User Interface as expected by the buildUserInterface() method of a DSP.
 * This abstract class contains only the method that the Faust compiler can
 * generate to describe a DSP user interface.
 ******************************************************************************/

struct Soundfile;

template <typename REAL>
struct FAUST_API UIReal {
    
    UIReal() {}
    virtual ~UIReal() {}
    
    // -- widget's layouts
    
    virtual void openTabBox(const char* label) = 0;
    virtual void openHorizontalBox(const char* label) = 0;
    virtual void openVerticalBox(const char* label) = 0;
    virtual void closeBox() = 0;
    
    // -- active widgets
    
    virtual void addButton(const char* label, REAL* zone) = 0;
    virtual void addCheckButton(const char* label, REAL* zone) = 0;
    virtual void addVerticalSlider(const char* label, REAL* zone, REAL init, REAL min, REAL max, REAL step) = 0;
    virtual void addHorizontalSlider(const char* label, REAL* zone, REAL init, REAL min, REAL max, REAL step) = 0;
    virtual void addNumEntry(const char* label, REAL* zone, REAL init, REAL min, REAL max, REAL step) = 0;
    
    // -- passive widgets
    
    virtual void addHorizontalBargraph(const char* label, REAL* zone, REAL min, REAL max) = 0;
    virtual void addVerticalBargraph(const char* label, REAL* zone, REAL min, REAL max) = 0;
    
    // -- soundfiles
    
    virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) = 0;
    
    // -- metadata declarations
    
    virtual void declare(REAL* /*zone*/, const char* /*key*/, const char* /*val*/) {}

    // To be used by LLVM client
    virtual int sizeOfFAUSTFLOAT() { return sizeof(FAUSTFLOAT); }
};

struct FAUST_API UI : public UIReal<FAUSTFLOAT> {
    UI() {}
    virtual ~UI() {}
#ifdef DAISY_NO_RTTI
    virtual bool isSoundUI() const { return false; }
    virtual bool isMidiInterface() const { return false; }
#endif
};

#endif
/**************************  END  UI.h **************************/
/************************** BEGIN PathBuilder.h **************************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __PathBuilder__
#define __PathBuilder__

#include <vector>
#include <set>
#include <map>
#include <string>
#include <algorithm>


/*******************************************************************************
 * PathBuilder : Faust User Interface
 * Helper class to build complete hierarchical path for UI items.
 ******************************************************************************/

class FAUST_API PathBuilder {

    protected:
    
        std::vector<std::string> fControlsLevel;
        std::vector<std::string> fFullPaths;
        std::map<std::string, std::string> fFull2Short;  // filled by computeShortNames()
    
        /**
         * @brief check if a character is acceptable for an ID
         *
         * @param c
         * @return true is the character is acceptable for an ID
         */
        bool isIDChar(char c) const
        {
            return ((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z')) || ((c >= '0') && (c <= '9'));
        }
    
        /**
         * @brief remove all "/0x00" parts
         *
         * @param src
         * @return modified string
         */
        std::string remove0x00(const std::string& src_aux) const
        {
            std::string src = src_aux;
            std::string from = "/0x00";
            std::string to = "";
            size_t pos = std::string::npos;
            while ((pos = src.find(from)) && (pos != std::string::npos)) {
                src = src.replace(pos, from.length(), to);
            }
            return src;
        }
    
        /**
         * @brief replace all non ID char with '_' (one '_' may replace several non ID char)
         *
         * @param src
         * @return modified string
         */
        std::string str2ID(const std::string& src) const
        {
            std::string dst;
            bool need_underscore = false;
            for (char c : src) {
                if (isIDChar(c) || (c == '/')) {
                    if (need_underscore) {
                        dst.push_back('_');
                        need_underscore = false;
                    }
                    dst.push_back(c);
                } else {
                    need_underscore = true;
                }
            }
            return dst;
        }
    
        /**
         * @brief Keep only the last n slash-parts
         *
         * @param src
         * @param n : 1 indicates the last slash-part
         * @return modified string
         */
        std::string cut(const std::string& src, int n) const
        {
            std::string rdst;
            for (int i = int(src.length())-1; i >= 0; i--) {
                char c = src[i];
                if (c != '/') {
                    rdst.push_back(c);
                } else if (n == 1) {
                    std::string dst;
                    for (int j = int(rdst.length())-1; j >= 0; j--) {
                        dst.push_back(rdst[j]);
                    }
                    return dst;
                } else {
                    n--;
                    rdst.push_back(c);
                }
            }
            return src;
        }
    
        void addFullPath(const std::string& label) { fFullPaths.push_back(buildPath(label)); }
    
        /**
         * @brief Compute the mapping between full path and short names
         */
        void computeShortNames()
        {
            std::vector<std::string>           uniquePaths;  // all full paths transformed but made unique with a prefix
            std::map<std::string, std::string> unique2full;  // all full paths transformed but made unique with a prefix
            char num_buffer[16];
            int pnum = 0;
            
            for (const auto& s : fFullPaths) {
                // Using snprintf since Teensy does not have the std::to_string function
                snprintf(num_buffer, 16, "%d", pnum++);
                std::string u = "/P" + std::string(num_buffer) + str2ID(remove0x00(s));
                uniquePaths.push_back(u);
                unique2full[u] = s;  // remember the full path associated to a unique path
            }
        
            std::map<std::string, int> uniquePath2level;                // map path to level
            for (const auto& s : uniquePaths) uniquePath2level[s] = 1;   // we init all levels to 1
            bool have_collisions = true;
        
            while (have_collisions) {
                // compute collision list
                std::set<std::string>              collisionSet;
                std::map<std::string, std::string> short2full;
                have_collisions = false;
                for (const auto& it : uniquePath2level) {
                    std::string u = it.first;
                    int n = it.second;
                    std::string shortName = cut(u, n);
                    auto p = short2full.find(shortName);
                    if (p == short2full.end()) {
                        // no collision
                        short2full[shortName] = u;
                    } else {
                        // we have a collision, add the two paths to the collision set
                        have_collisions = true;
                        collisionSet.insert(u);
                        collisionSet.insert(p->second);
                    }
                }
                for (const auto& s : collisionSet) uniquePath2level[s]++;  // increase level of colliding path
            }
        
            for (const auto& it : uniquePath2level) {
                std::string u = it.first;
                int n = it.second;
                std::string shortName = replaceCharList(cut(u, n), {'/'}, '_');
                fFull2Short[unique2full[u]] = shortName;
            }
        }
    
        std::string replaceCharList(const std::string& str, const std::vector<char>& ch1, char ch2)
        {
            auto beg = ch1.begin();
            auto end = ch1.end();
            std::string res = str;
            for (size_t i = 0; i < str.length(); ++i) {
                if (std::find(beg, end, str[i]) != end) res[i] = ch2;
            }
            return res;
        }
     
    public:
    
        PathBuilder() {}
        virtual ~PathBuilder() {}
    
        // Return true for the first level of groups
        bool pushLabel(const std::string& label_aux)
        {
            std::string label = replaceCharList(label_aux, {'/'}, '_');
            fControlsLevel.push_back(label); return fControlsLevel.size() == 1;
        }
    
        // Return true for the last level of groups
        bool popLabel() { fControlsLevel.pop_back(); return fControlsLevel.size() == 0; }
    
        // Return a complete path built from a label
        std::string buildPath(const std::string& label_aux)
        {
            std::string label = replaceCharList(label_aux, {'/'}, '_');
            std::string res = "/";
            for (size_t i = 0; i < fControlsLevel.size(); i++) {
                res = res + fControlsLevel[i] + "/";
            }
            res += label;
            return replaceCharList(res, {' ', '#', '*', ',', '?', '[', ']', '{', '}', '(', ')'}, '_');
        }
    
        // Assuming shortnames have been built, return the shortname from a label
        std::string buildShortname(const std::string& label)
        {
            return (hasShortname()) ? fFull2Short[buildPath(label)] : "";
        }
    
        bool hasShortname() { return fFull2Short.size() > 0; }
    
};

#endif  // __PathBuilder__
/**************************  END  PathBuilder.h **************************/

/*******************************************************************************
 * MapUI : Faust User Interface.
 *
 * This class creates:
 * - a map of 'labels' and zones for each UI item.
 * - a map of unique 'shortname' (built so that they never collide) and zones for each UI item
 * - a map of complete hierarchical 'paths' and zones for each UI item
 *
 * Simple 'labels', 'shortname' and complete 'paths' (to fully discriminate between possible same
 * 'labels' at different location in the UI hierachy) can be used to access a given parameter.
 ******************************************************************************/

class FAUST_API MapUI : public UI, public PathBuilder
{
    
    protected:
    
        // Label zone map
        std::map<std::string, FAUSTFLOAT*> fLabelZoneMap;
    
        // Shortname zone map
        std::map<std::string, FAUSTFLOAT*> fShortnameZoneMap;
    
        // Full path map
        std::map<std::string, FAUSTFLOAT*> fPathZoneMap;
    
        void addZoneLabel(const std::string& label, FAUSTFLOAT* zone)
        {
            std::string path = buildPath(label);
            fFullPaths.push_back(path);
            fPathZoneMap[path] = zone;
            fLabelZoneMap[label] = zone;
        }
    
    public:
        
        MapUI() {}
        virtual ~MapUI() {}
        
        // -- widget's layouts
        void openTabBox(const char* label)
        {
            pushLabel(label);
        }
        void openHorizontalBox(const char* label)
        {
            pushLabel(label);
        }
        void openVerticalBox(const char* label)
        {
            pushLabel(label);
        }
        void closeBox()
        {
            if (popLabel()) {
                // Shortnames can be computed when all fullnames are known
                computeShortNames();
                // Fill 'shortname' map
                for (const auto& it : fFullPaths) {
                    fShortnameZoneMap[fFull2Short[it]] = fPathZoneMap[it];
                }
            }
        }
        
        // -- active widgets
        void addButton(const char* label, FAUSTFLOAT* zone)
        {
            addZoneLabel(label, zone);
        }
        void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            addZoneLabel(label, zone);
        }
        void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            addZoneLabel(label, zone);
        }
        void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            addZoneLabel(label, zone);
        }
        void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            addZoneLabel(label, zone);
        }
        
        // -- passive widgets
        void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
        {
            addZoneLabel(label, zone);
        }
        void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
        {
            addZoneLabel(label, zone);
        }
    
        // -- soundfiles
        virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) {}
        
        // -- metadata declarations
        virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val)
        {}
    
        //-------------------------------------------------------------------------------
        // Public API
        //-------------------------------------------------------------------------------
    
        /**
         * Set the param value.
         *
         * @param str - the UI parameter label/shortname/path
         * @param value - the UI parameter value
         *
         */
        void setParamValue(const std::string& str, FAUSTFLOAT value)
        {
            const auto fPathZoneMapIter = fPathZoneMap.find(str);
            if (fPathZoneMapIter != fPathZoneMap.end()) {
                *fPathZoneMapIter->second = value;
                return;
            }
            
            const auto fShortnameZoneMapIter = fShortnameZoneMap.find(str);
            if (fShortnameZoneMapIter != fShortnameZoneMap.end()) {
                *fShortnameZoneMapIter->second = value;
                return;
            }
            
            const auto fLabelZoneMapIter = fLabelZoneMap.find(str);
            if (fLabelZoneMapIter != fLabelZoneMap.end()) {
                *fLabelZoneMapIter->second = value;
                return;
            }
            
            fprintf(stderr, "ERROR : setParamValue '%s' not found\n", str.c_str());
        }
        
        /**
         * Return the param value.
         *
         * @param str - the UI parameter label/shortname/path
         *
         * @return the param value.
         */
        FAUSTFLOAT getParamValue(const std::string& str) const
        {
            const auto fPathZoneMapIter = fPathZoneMap.find(str);
            if (fPathZoneMapIter != fPathZoneMap.end()) {
                return *fPathZoneMapIter->second;
            }
            
            const auto fShortnameZoneMapIter = fShortnameZoneMap.find(str);
            if (fShortnameZoneMapIter != fShortnameZoneMap.end()) {
                return *fShortnameZoneMapIter->second;
            }
            
            const auto fLabelZoneMapIter = fLabelZoneMap.find(str);
            if (fLabelZoneMapIter != fLabelZoneMap.end()) {
                return *fLabelZoneMapIter->second;
            }
            
            fprintf(stderr, "ERROR : getParamValue '%s' not found\n", str.c_str());
            return 0;
        }
    
        // map access 
        std::map<std::string, FAUSTFLOAT*>& getFullpathMap() { return fPathZoneMap; }
        std::map<std::string, FAUSTFLOAT*>& getShortnameMap() { return fShortnameZoneMap; }
        std::map<std::string, FAUSTFLOAT*>& getLabelMap() { return fLabelZoneMap; }
            
        /**
         * Return the number of parameters in the UI.
         *
         * @return the number of parameters
         */
        int getParamsCount() const { return int(fPathZoneMap.size()); }
        
        /**
         * Return the param path.
         *
         * @param index - the UI parameter index
         *
         * @return the param path
         */
        std::string getParamAddress(int index) const
        {
            if (index < 0 || index > int(fPathZoneMap.size())) {
                return "";
            } else {
                auto it = fPathZoneMap.begin();
                while (index-- > 0 && it++ != fPathZoneMap.end()) {}
                return it->first;
            }
        }
        
        const char* getParamAddress1(int index) const
        {
            if (index < 0 || index > int(fPathZoneMap.size())) {
                return nullptr;
            } else {
                auto it = fPathZoneMap.begin();
                while (index-- > 0 && it++ != fPathZoneMap.end()) {}
                return it->first.c_str();
            }
        }
    
        /**
         * Return the param shortname.
         *
         * @param index - the UI parameter index
         *
         * @return the param shortname
         */
        std::string getParamShortname(int index) const
        {
            if (index < 0 || index > int(fShortnameZoneMap.size())) {
                return "";
            } else {
                auto it = fShortnameZoneMap.begin();
                while (index-- > 0 && it++ != fShortnameZoneMap.end()) {}
                return it->first;
            }
        }
        
        const char* getParamShortname1(int index) const
        {
            if (index < 0 || index > int(fShortnameZoneMap.size())) {
                return nullptr;
            } else {
                auto it = fShortnameZoneMap.begin();
                while (index-- > 0 && it++ != fShortnameZoneMap.end()) {}
                return it->first.c_str();
            }
        }
    
        /**
         * Return the param label.
         *
         * @param index - the UI parameter index
         *
         * @return the param label
         */
        std::string getParamLabel(int index) const
        {
            if (index < 0 || index > int(fLabelZoneMap.size())) {
                return "";
            } else {
                auto it = fLabelZoneMap.begin();
                while (index-- > 0 && it++ != fLabelZoneMap.end()) {}
                return it->first;
            }
        }
        
        const char* getParamLabel1(int index) const
        {
            if (index < 0 || index > int(fLabelZoneMap.size())) {
                return nullptr;
            } else {
                auto it = fLabelZoneMap.begin();
                while (index-- > 0 && it++ != fLabelZoneMap.end()) {}
                return it->first.c_str();
            }
        }
    
        /**
         * Return the param path.
         *
         * @param zone - the UI parameter memory zone
         *
         * @return the param path
         */
        std::string getParamAddress(FAUSTFLOAT* zone) const
        {
            for (const auto& it : fPathZoneMap) {
                if (it.second == zone) return it.first;
            }
            return "";
        }
    
        /**
         * Return the param memory zone.
         *
         * @param zone - the UI parameter label/shortname/path
         *
         * @return the param path
         */
        FAUSTFLOAT* getParamZone(const std::string& str) const
        {
            const auto fPathZoneMapIter = fPathZoneMap.find(str);
            if (fPathZoneMapIter != fPathZoneMap.end()) {
                return fPathZoneMapIter->second;
            }
            
            const auto fShortnameZoneMapIter = fShortnameZoneMap.find(str);
            if (fShortnameZoneMapIter != fShortnameZoneMap.end()) {
                return fShortnameZoneMapIter->second;
            }
            
            const auto fLabelZoneMapIter = fLabelZoneMap.find(str);
            if (fLabelZoneMapIter != fLabelZoneMap.end()) {
                return fLabelZoneMapIter->second;
            }

            return nullptr;
        }
    
        /**
         * Return the param memory zone.
         *
         * @param zone - the UI parameter index
         *
         * @return the param path
         */
        FAUSTFLOAT* getParamZone(int index) const 
        {
            if (index < 0 || index > int(fPathZoneMap.size())) {
                return nullptr;
            } else {
                auto it = fPathZoneMap.begin();
                while (index-- > 0 && it++ != fPathZoneMap.end()) {}
                return it->second;
            }
        }
    
        static bool endsWith(const std::string& str, const std::string& end)
        {
            size_t l1 = str.length();
            size_t l2 = end.length();
            return (l1 >= l2) && (0 == str.compare(l1 - l2, l2, end));
        }
    
};

#endif // FAUST_MAPUI_H
/**************************  END  MapUI.h **************************/
/************************** BEGIN meta.h *******************************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __meta__
#define __meta__


/**
 The base class of Meta handler to be used in dsp::metadata(Meta* m) method to retrieve (key, value) metadata.
 */
struct FAUST_API Meta {
    virtual ~Meta() {}
    virtual void declare(const char* key, const char* value) = 0;
};

#endif
/**************************  END  meta.h **************************/
/************************** BEGIN dsp.h ********************************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __dsp__
#define __dsp__

#include <string>
#include <vector>
#include <cstdint>


#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

struct FAUST_API UI;
struct FAUST_API Meta;

/**
 * DSP memory manager.
 */

struct FAUST_API dsp_memory_manager {
    
    enum MemType { kInt32, kInt32_ptr, kFloat, kFloat_ptr, kDouble, kDouble_ptr, kQuad, kQuad_ptr, kFixedPoint, kFixedPoint_ptr, kObj, kObj_ptr, kSound, kSound_ptr };

    virtual ~dsp_memory_manager() = default;
    
    /**
     * Inform the Memory Manager with the number of expected memory zones.
     * @param count - the number of expected memory zones
     */
    virtual void begin(size_t count) {}
    
    /**
     * Give the Memory Manager information on a given memory zone.
     * @param name - the memory zone name
     * @param type - the memory zone type (in MemType)
     * @param size - the size in unit of the memory type of the memory zone
     * @param size_bytes - the size in bytes of the memory zone
     * @param reads - the number of Read access to the zone used to compute one frame
     * @param writes - the number of Write access to the zone used to compute one frame
     */
    virtual void info(const char* name, MemType type, size_t size, size_t size_bytes, size_t reads, size_t writes) {}
  
    /**
     * Inform the Memory Manager that all memory zones have been described,
     * to possibly start a 'compute the best allocation strategy' step.
     */
    virtual void end() {}
    
    /**
     * Allocate a memory zone.
     * @param size - the memory zone size in bytes
     */
    virtual void* allocate(size_t size) = 0;
    
    /**
     * Destroy a memory zone.
     * @param ptr - the memory zone pointer to be deallocated
     */
    virtual void destroy(void* ptr) = 0;
    
};

/**
* Signal processor definition.
*/

class FAUST_API dsp {

    public:

        dsp() = default;
        virtual ~dsp() = default;

        /* Return instance number of audio inputs */
        virtual int getNumInputs() = 0;
    
        /* Return instance number of audio outputs */
        virtual int getNumOutputs() = 0;
    
        /**
         * Trigger the ui_interface parameter with instance specific calls
         * to 'openTabBox', 'addButton', 'addVerticalSlider'... in order to build the UI.
         *
         * @param ui_interface - the user interface builder
         */
        virtual void buildUserInterface(UI* ui_interface) = 0;
    
        /* Return the sample rate currently used by the instance */
        virtual int getSampleRate() = 0;
    
        /**
         * Global init, calls the following methods:
         * - static class 'classInit': static tables initialization
         * - 'instanceInit': constants and instance state initialization
         *
         * @param sample_rate - the sampling rate in Hz
         */
        virtual void init(int sample_rate) = 0;

        /**
         * Init instance state.
         *
         * @param sample_rate - the sampling rate in Hz
         */
        virtual void instanceInit(int sample_rate) = 0;
    
        /**
         * Init instance constant state.
         *
         * @param sample_rate - the sampling rate in Hz
         */
        virtual void instanceConstants(int sample_rate) = 0;
    
        /* Init default control parameters values */
        virtual void instanceResetUserInterface() = 0;
    
        /* Init instance state (like delay lines...) but keep the control parameter values */
        virtual void instanceClear() = 0;
 
        /**
         * Return a clone of the instance.
         *
         * @return a copy of the instance on success, otherwise a null pointer.
         */
        virtual ::dsp* clone() = 0;
    
        /**
         * Trigger the Meta* m parameter with instance specific calls to 'declare' (key, value) metadata.
         *
         * @param m - the Meta* meta user
         */
        virtual void metadata(Meta* m) = 0;

    
        /**
         * Read all controllers (buttons, sliders, etc.), and update the DSP state to be used by 'frame' or 'compute'.
         * This method will be filled with the -ec (--external-control) option.
         */
        virtual void control() {}
    
        /**
         * DSP instance computation to process one single frame.
         *
         * Note that by default inputs and outputs buffers are supposed to be distinct memory zones,
         * so one cannot safely write frame(inputs, inputs).
         * The -inpl option can be used for that, but only in scalar mode for now.
         * This method will be filled with the -os (--one-sample) option.
         *
         * @param inputs - the input audio buffers as an array of FAUSTFLOAT samples (eiher float, double or quad)
         * @param outputs - the output audio buffers as an array of FAUSTFLOAT samples (eiher float, double or quad)
         */
        virtual void frame(FAUSTFLOAT* inputs, FAUSTFLOAT* outputs) {}
        
        /**
         * DSP instance computation to be called with successive in/out audio buffers.
         *
         * Note that by default inputs and outputs buffers are supposed to be distinct memory zones,
         * so one cannot safely write compute(count, inputs, inputs).
         * The -inpl compilation option can be used for that, but only in scalar mode for now.
         *
         * @param count - the number of frames to compute
         * @param inputs - the input audio buffers as an array of non-interleaved FAUSTFLOAT buffers
         * (containing either float, double or quad samples)
         * @param outputs - the output audio buffers as an array of non-interleaved FAUSTFLOAT buffers
         * (containing either float, double or quad samples)
         */
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) = 0;
    
        /**
         * Alternative DSP instance computation method for use by subclasses, incorporating an additional `date_usec` parameter,
         * which specifies the timestamp of the first sample in the audio buffers.
         *
         * @param date_usec - the timestamp in microsec given by audio driver. By convention timestamp of -1 means 'no timestamp conversion',
         * events already have a timestamp expressed in frames.
         * @param count - the number of frames to compute
         * @param inputs - the input audio buffers as an array of non-interleaved FAUSTFLOAT samples (either float, double or quad)
         * @param outputs - the output audio buffers as an array of non-interleaved FAUSTFLOAT samples (either float, double or quad)
         */
        virtual void compute(double /*date_usec*/, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { compute(count, inputs, outputs); }
       
};

/**
 * Generic DSP decorator.
 */

class FAUST_API decorator_dsp : public ::dsp {

    protected:

        ::dsp* fDSP;

    public:

        decorator_dsp(::dsp* dsp = nullptr):fDSP(dsp) {}
        virtual ~decorator_dsp() { delete fDSP; }

        virtual int getNumInputs() override { return fDSP->getNumInputs(); }
        virtual int getNumOutputs() override { return fDSP->getNumOutputs(); }
        virtual void buildUserInterface(UI* ui_interface) override { fDSP->buildUserInterface(ui_interface); }
        virtual int getSampleRate() override { return fDSP->getSampleRate(); }
        virtual void init(int sample_rate) override { fDSP->init(sample_rate); }
        virtual void instanceInit(int sample_rate) override { fDSP->instanceInit(sample_rate); }
        virtual void instanceConstants(int sample_rate) override { fDSP->instanceConstants(sample_rate); }
        virtual void instanceResetUserInterface() override { fDSP->instanceResetUserInterface(); }
        virtual void instanceClear() override { fDSP->instanceClear(); }
        virtual decorator_dsp* clone() override { return new decorator_dsp(fDSP->clone()); }
        virtual void metadata(Meta* m) override { fDSP->metadata(m); }
        // Beware: subclasses usually have to overload the two 'compute' methods
        virtual void control() override { fDSP->control(); }
        virtual void frame(FAUSTFLOAT* inputs, FAUSTFLOAT* outputs) override { fDSP->frame(inputs, outputs); }
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) override { fDSP->compute(count, inputs, outputs); }
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) override { fDSP->compute(date_usec, count, inputs, outputs); }
    
};

/**
 * DSP factory class, used with LLVM and Interpreter backends
 * to create DSP instances from a compiled DSP program.
 */

class FAUST_API dsp_factory {
    
    protected:
    
        // So that to force sub-classes to use deleteDSPFactory(dsp_factory* factory);
        virtual ~dsp_factory() = default;
    
    public:
    
        /* Return factory name */
        virtual std::string getName() = 0;
    
        /* Return factory SHA key */
        virtual std::string getSHAKey() = 0;
    
        /* Return factory expanded DSP code */
        virtual std::string getDSPCode() = 0;
    
        /* Return factory compile options */
        virtual std::string getCompileOptions() = 0;
    
        /* Get the Faust DSP factory list of library dependancies */
        virtual std::vector<std::string> getLibraryList() = 0;
    
        /* Get the list of all used includes */
        virtual std::vector<std::string> getIncludePathnames() = 0;
    
        /* Get warning messages list for a given compilation */
        virtual std::vector<std::string> getWarningMessages() = 0;

        /* Return JSON description of the DSP (UI + metadata) */
        virtual std::string getJSON() = 0;
    
        /* Create a new DSP instance, to be deleted with C++ 'delete' */
        virtual ::dsp* createDSPInstance() = 0;
    
        /* Static tables initialization, possibly implemened in sub-classes*/
        virtual void classInit(int sample_rate) {};
    
        /* Set a custom memory manager to be used when creating instances */
        virtual void setMemoryManager(dsp_memory_manager* manager) = 0;
    
        /* Return the currently set custom memory manager */
        virtual dsp_memory_manager* getMemoryManager() = 0;
    
};

// Denormal handling

#if defined (__SSE__)
#include <xmmintrin.h>
#endif

class FAUST_API ScopedNoDenormals {
    
    private:
    
        intptr_t fpsr = 0;
        
        void setFpStatusRegister(intptr_t fpsr_aux) noexcept
        {
        #if defined (__arm64__) || defined (__aarch64__)
            asm volatile("msr fpcr, %0" : : "ri" (fpsr_aux));
        #elif defined (__SSE__)
            // The volatile keyword here is needed to workaround a bug in AppleClang 13.0
            // which aggressively optimises away the variable otherwise
            volatile uint32_t fpsr_w = static_cast<uint32_t>(fpsr_aux);
            _mm_setcsr(fpsr_w);
        #endif
        }
        
        void getFpStatusRegister() noexcept
        {
        #if defined (__arm64__) || defined (__aarch64__)
            asm volatile("mrs %0, fpcr" : "=r" (fpsr));
        #elif defined (__SSE__)
            fpsr = static_cast<intptr_t>(_mm_getcsr());
        #endif
        }
    
    public:
    
        ScopedNoDenormals() noexcept
        {
        #if defined (__arm64__) || defined (__aarch64__)
            intptr_t mask = (1 << 24 /* FZ */);
        #elif defined (__SSE__)
        #if defined (__SSE2__)
            intptr_t mask = 0x8040;
        #else
            intptr_t mask = 0x8000;
        #endif
        #else
            intptr_t mask = 0x0000;
        #endif
            getFpStatusRegister();
            setFpStatusRegister(fpsr | mask);
        }
        
        ~ScopedNoDenormals() noexcept
        {
            setFpStatusRegister(fpsr);
        }

};

#define AVOIDDENORMALS ScopedNoDenormals ftz_scope;

#endif

/************************** END dsp.h **************************/

// BEGIN-FAUSTDSP


#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

/* link with : "" */
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

#if defined(_WIN32)
#define RESTRICT __restrict
#else
#define RESTRICT __restrict__
#endif

static float mydsp_faustpower2_f(float value) {
	return value * value;
}
static float mydsp_faustpower3_f(float value) {
	return value * value * value;
}

class mydsp : public dsp {
	
 private:
	
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT fCheckbox1;
	int fSampleRate;
	float fConst0;
	float fConst1;
	float fConst2;
	float fConst3;
	float fConst4;
	float fConst5;
	float fConst6;
	float fConst7;
	float fConst8;
	float fConst9;
	float fConst10;
	float fConst11;
	float fConst12;
	float fConst13;
	float fConst14;
	float fConst15;
	float fConst16;
	float fConst17;
	float fConst18;
	float fConst19;
	float fConst20;
	float fConst21;
	float fConst22;
	float fConst23;
	float fConst24;
	float fConst25;
	float fConst26;
	float fConst27;
	float fConst28;
	float fConst29;
	float fConst30;
	float fConst31;
	float fConst32;
	float fConst33;
	float fConst34;
	float fConst35;
	FAUSTFLOAT fCheckbox2;
	float fConst36;
	float fConst37;
	float fConst38;
	float fConst39;
	float fConst40;
	float fConst41;
	float fConst42;
	float fConst43;
	float fConst44;
	float fConst45;
	float fConst46;
	float fConst47;
	float fConst48;
	float fConst49;
	float fConst50;
	float fConst51;
	float fConst52;
	float fConst53;
	float fConst54;
	float fConst55;
	float fConst56;
	float fConst57;
	float fConst58;
	float fConst59;
	float fConst60;
	float fConst61;
	float fConst62;
	float fConst63;
	float fConst64;
	float fConst65;
	float fConst66;
	float fConst67;
	float fConst68;
	float fConst69;
	float fConst70;
	float fConst71;
	float fConst72;
	float fConst73;
	float fConst74;
	float fConst75;
	float fVec0[2];
	float fRec25[2];
	float fConst76;
	float fConst77;
	float fRec27[2];
	FAUSTFLOAT fHslider0;
	int iVec1[2];
	int iConst78;
	int iRec28[2];
	float fConst79;
	float fRec26[2];
	float fVec2[2];
	float fRec24[2];
	float fConst80;
	float fConst81;
	float fConst82;
	float fRec23[3];
	float fConst83;
	float fConst84;
	float fRec22[3];
	float fVec3[2];
	float fRec21[2];
	float fRec20[2];
	float fConst85;
	FAUSTFLOAT fHslider1;
	float fConst86;
	float fRec29[2];
	float fVec4[2];
	float fRec19[2];
	float fRec18[2];
	float fRec17[2];
	float fVec5[2];
	float fRec16[2];
	float fRec15[2];
	float fRec14[2];
	float fVec6[2];
	float fRec13[2];
	float fConst87;
	float fConst88;
	float fConst89;
	float fRec12[4];
	float fConst90;
	float fConst91;
	float fConst92;
	float fRec11[3];
	float fConst93;
	float fConst94;
	float fConst95;
	float fConst96;
	float fConst97;
	float fRec30[3];
	float fConst98;
	float fRec10[3];
	float fConst99;
	float fConst100;
	float fConst101;
	float fVec7[2];
	float fRec9[2];
	float fConst102;
	float fRec31[2];
	FAUSTFLOAT fHslider2;
	float fRec32[2];
	float fVec8[2];
	float fRec8[2];
	float fConst103;
	float fConst104;
	float fConst105;
	float fRec7[3];
	float fConst106;
	float fRec6[3];
	float fConst107;
	float fConst108;
	float fConst109;
	float fConst110;
	float fRec5[3];
	float fConst111;
	float fConst112;
	float fConst113;
	float fConst114;
	float fRec4[3];
	float fConst115;
	float fConst116;
	float fConst117;
	int IOTA0;
	float fVec9[256];
	int iConst118;
	float fConst119;
	float fConst120;
	float fRec3[3];
	float fConst121;
	float fRec2[3];
	float fConst122;
	float fConst123;
	float fConst124;
	float fRec1[3];
	float fVec10[2];
	float fRec0[2];
	
 public:
	mydsp() {
	}
	
	mydsp(const mydsp&) = default;
	
	virtual ~mydsp() = default;
	
	mydsp& operator=(const mydsp&) = default;
	
	void metadata(Meta* m) { 
		m->declare("analyzers.lib/amp_follower_ar:author", "Jonatan Liljedahl, revised by Romain Michon");
		m->declare("analyzers.lib/name", "Faust Analyzer Library");
		m->declare("analyzers.lib/version", "1.3.0");
		m->declare("basics.lib/bypass1:author", "Julius Smith");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "1.23.0");
		m->declare("compile_options", "-a ../../faustMinimal.h -lang cpp -i -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "1.2.0");
		m->declare("filename", "Dunwich.dsp");
		m->declare("filters.lib/dcblockerat:author", "Julius O. Smith III");
		m->declare("filters.lib/dcblockerat:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/dcblockerat:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/filterbank:author", "Julius O. Smith III");
		m->declare("filters.lib/filterbank:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/filterbank:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/fir:author", "Julius O. Smith III");
		m->declare("filters.lib/fir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/fir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/highpass:author", "Julius O. Smith III");
		m->declare("filters.lib/highpass:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/highshelf:author", "Julius O. Smith III");
		m->declare("filters.lib/highshelf:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/highshelf:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/iir:author", "Julius O. Smith III");
		m->declare("filters.lib/iir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/iir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1:author", "Julius O. Smith III");
		m->declare("filters.lib/lowpass:author", "Julius O. Smith III");
		m->declare("filters.lib/lowpass:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/lowpass:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/peak_eq:author", "Julius O. Smith III");
		m->declare("filters.lib/peak_eq:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/peak_eq:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/peak_eq_cq:author", "Julius O. Smith III");
		m->declare("filters.lib/peak_eq_cq:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/peak_eq_cq:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/pole:author", "Julius O. Smith III");
		m->declare("filters.lib/pole:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/pole:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf1:author", "Julius O. Smith III");
		m->declare("filters.lib/tf1:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf1:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf1s:author", "Julius O. Smith III");
		m->declare("filters.lib/tf1s:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf1s:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf2:author", "Julius O. Smith III");
		m->declare("filters.lib/tf2:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf2:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf2s:author", "Julius O. Smith III");
		m->declare("filters.lib/tf2s:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf2s:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/version", "1.7.1");
		m->declare("filters.lib/zero:author", "Julius O. Smith III");
		m->declare("filters.lib/zero:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/zero:license", "MIT-style STK-4.3 license");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.9.0");
		m->declare("misceffects.lib/gate_gain_mono:author", "Julius O. Smith III");
		m->declare("misceffects.lib/gate_gain_mono:license", "STK-4.3");
		m->declare("misceffects.lib/gate_mono:author", "Julius O. Smith III");
		m->declare("misceffects.lib/gate_mono:license", "STK-4.3");
		m->declare("misceffects.lib/name", "Misc Effects Library");
		m->declare("misceffects.lib/version", "2.5.2");
		m->declare("name", "Dunwich");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "1.3.0");
		m->declare("signals.lib/name", "Faust Routing Library");
		m->declare("signals.lib/onePoleSwitching:author", "Jonatan Liljedahl, revised by Dario Sanfilippo");
		m->declare("signals.lib/onePoleSwitching:licence", "STK-4.3");
		m->declare("signals.lib/version", "1.6.0");
		m->declare("tonestacks.lib/author", "Guitarix project (<http://guitarix.sourceforge.net/>)");
		m->declare("tonestacks.lib/copyright", "Guitarix project");
		m->declare("tonestacks.lib/license", "LGPL");
		m->declare("tonestacks.lib/name", "Faust Tonestack Emulation Library");
		m->declare("tonestacks.lib/version", "1.28.0");
	}

	virtual int getNumInputs() {
		return 1;
	}
	virtual int getNumOutputs() {
		return 1;
	}
	
	static void classInit(int sample_rate) {
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = std::min<float>(1.92e+05f, std::max<float>(1.0f, static_cast<float>(fSampleRate)));
		fConst1 = 109.95574f / fConst0;
		fConst2 = 1.0f / (fConst1 + 1.0f);
		fConst3 = 1.0f - fConst1;
		fConst4 = std::tan(26703.537f / fConst0);
		fConst5 = 1.0f / fConst4;
		fConst6 = (fConst5 + 1.4142135f) / fConst4 + 1.0f;
		fConst7 = 1.05f / fConst6;
		fConst8 = std::tan(15079.645f / fConst0);
		fConst9 = 1.0f / fConst8;
		fConst10 = 1.0f / ((fConst9 + 0.76536685f) / fConst8 + 1.0f);
		fConst11 = 1.0f / ((fConst9 + 1.847759f) / fConst8 + 1.0f);
		fConst12 = 1507.9645f / fConst0;
		fConst13 = std::tan(fConst12);
		fConst14 = 1.0f / fConst13;
		fConst15 = fConst0 * std::sin(3015.929f / fConst0);
		fConst16 = 1504.1802f / fConst15;
		fConst17 = 1.0f / ((fConst14 + fConst16) / fConst13 + 1.0f);
		fConst18 = 2.0f * (1.0f - 1.0f / mydsp_faustpower2_f(fConst13));
		fConst19 = std::tan(753.98224f / fConst0);
		fConst20 = 1.0f / fConst19;
		fConst21 = fConst0 * std::sin(fConst12);
		fConst22 = 418.87903f / fConst21;
		fConst23 = 1.0f / ((fConst20 + fConst22) / fConst19 + 1.0f);
		fConst24 = 2.0f * (1.0f - 1.0f / mydsp_faustpower2_f(fConst19));
		fConst25 = std::tan(361.28314f / fConst0);
		fConst26 = 1.0f / fConst25;
		fConst27 = fConst0 * std::sin(722.5663f / fConst0);
		fConst28 = 164.21962f / fConst27;
		fConst29 = 1.0f / ((fConst26 + fConst28) / fConst25 + 1.0f);
		fConst30 = 2.0f * (1.0f - 1.0f / mydsp_faustpower2_f(fConst25));
		fConst31 = std::tan(235.61945f / fConst0);
		fConst32 = mydsp_faustpower2_f(fConst31);
		fConst33 = 1.0f / fConst31;
		fConst34 = (fConst33 + 1.4142135f) / fConst31 + 1.0f;
		fConst35 = 1.0f / (fConst32 * fConst34);
		fConst36 = std::tan(15707.963f / fConst0);
		fConst37 = 1.0f / fConst36;
		fConst38 = 1.0f / (fConst37 + 1.0f);
		fConst39 = 1.0f - fConst37;
		fConst40 = std::tan(251.32741f / fConst0);
		fConst41 = 1.0f / fConst40;
		fConst42 = fConst0 * std::sin(502.65482f / fConst0);
		fConst43 = 502.65482f / fConst42;
		fConst44 = (fConst41 + fConst43) / fConst40 + 1.0f;
		fConst45 = 1.0f / fConst44;
		fConst46 = 2.0f * (1.0f - 1.0f / mydsp_faustpower2_f(fConst40));
		fConst47 = std::tan(22996.459f / fConst0);
		fConst48 = 1.0f / fConst47;
		fConst49 = 1.0f / ((fConst48 + 1.4142135f) / fConst47 + 1.0f);
		fConst50 = 1.0f / std::tan(23247.785f / fConst0);
		fConst51 = 1.0f / (fConst50 + 1.0f);
		fConst52 = 1.0f - fConst50;
		fConst53 = 1.0f / std::tan(62.831852f / fConst0);
		fConst54 = 1.0f / (fConst53 + 1.0f);
		fConst55 = 1.0f - fConst53;
		fConst56 = 1.0f / std::tan(62831.85f / fConst0);
		fConst57 = 1.0f / (fConst56 + 1.0f);
		fConst58 = 1.0f - fConst56;
		fConst59 = 1.0f / std::tan(376.99112f / fConst0);
		fConst60 = 1.0f / (fConst59 + 1.0f);
		fConst61 = 1.0f - fConst59;
		fConst62 = 1.0f / std::tan(7225.663f / fConst0);
		fConst63 = 1.0f / (fConst62 + 1.0f);
		fConst64 = 1.0f - fConst62;
		fConst65 = 1.0f / std::tan(157.07964f / fConst0);
		fConst66 = 1.0f / (fConst65 + 1.0f);
		fConst67 = 1.0f - fConst65;
		fConst68 = std::tan(6283.1855f / fConst0);
		fConst69 = 1.0f / fConst68;
		fConst70 = 1.0f / ((fConst69 + 1.4142135f) / fConst68 + 1.0f);
		fConst71 = std::tan(12566.371f / fConst0);
		fConst72 = 1.0f / fConst71;
		fConst73 = (fConst72 + 1.4142135f) / fConst71 + 1.0f;
		fConst74 = 2e+01f / fConst73;
		fConst75 = 3.1415927f / fConst0;
		fConst76 = std::exp(-(2e+03f / fConst0));
		fConst77 = 1.0f - fConst76;
		iConst78 = static_cast<int>(0.01f * fConst0);
		fConst79 = std::exp(-(5e+01f / fConst0));
		fConst80 = 1.0f / fConst73;
		fConst81 = (fConst72 + -1.4142135f) / fConst71 + 1.0f;
		fConst82 = 2.0f * (1.0f - 1.0f / mydsp_faustpower2_f(fConst71));
		fConst83 = (fConst69 + -1.4142135f) / fConst68 + 1.0f;
		fConst84 = 2.0f * (1.0f - 1.0f / mydsp_faustpower2_f(fConst68));
		fConst85 = 44.1f / fConst0;
		fConst86 = 1.0f - fConst85;
		fConst87 = 2.0f * fConst0;
		fConst88 = mydsp_faustpower2_f(fConst87);
		fConst89 = mydsp_faustpower3_f(fConst87);
		fConst90 = 3.0f * fConst89;
		fConst91 = (fConst48 + -1.4142135f) / fConst47 + 1.0f;
		fConst92 = 2.0f * (1.0f - 1.0f / mydsp_faustpower2_f(fConst47));
		fConst93 = std::tan(35996.367f / fConst0);
		fConst94 = 1.0f / fConst93;
		fConst95 = 1.0f / ((fConst94 + 1.4142135f) / fConst93 + 1.0f);
		fConst96 = (fConst94 + -1.4142135f) / fConst93 + 1.0f;
		fConst97 = 2.0f * (1.0f - 1.0f / mydsp_faustpower2_f(fConst93));
		fConst98 = (fConst41 - fConst43) / fConst40 + 1.0f;
		fConst99 = 1002.9282f / fConst42;
		fConst100 = (fConst41 + fConst99) / fConst40 + 1.0f;
		fConst101 = (fConst41 - fConst99) / fConst40 + 1.0f;
		fConst102 = 1.0f / (fConst36 * fConst44);
		fConst103 = 1.0f / fConst34;
		fConst104 = (fConst33 + -1.4142135f) / fConst31 + 1.0f;
		fConst105 = 2.0f * (1.0f - 1.0f / fConst32);
		fConst106 = (fConst26 - fConst28) / fConst25 + 1.0f;
		fConst107 = 327.66122f / fConst27;
		fConst108 = (fConst26 + fConst107) / fConst25 + 1.0f;
		fConst109 = (fConst26 - fConst107) / fConst25 + 1.0f;
		fConst110 = (fConst20 - fConst22) / fConst19 + 1.0f;
		fConst111 = 527.33746f / fConst21;
		fConst112 = (fConst20 + fConst111) / fConst19 + 1.0f;
		fConst113 = (fConst20 - fConst111) / fConst19 + 1.0f;
		fConst114 = (fConst14 - fConst16) / fConst13 + 1.0f;
		fConst115 = 1005.30963f / fConst15;
		fConst116 = (fConst14 + fConst115) / fConst13 + 1.0f;
		fConst117 = (fConst14 - fConst115) / fConst13 + 1.0f;
		iConst118 = std::min<int>(1024, std::max<int>(0, static_cast<int>(0.00085f * fConst0)));
		fConst119 = (fConst9 + -1.847759f) / fConst8 + 1.0f;
		fConst120 = 2.0f * (1.0f - 1.0f / mydsp_faustpower2_f(fConst8));
		fConst121 = (fConst9 + -0.76536685f) / fConst8 + 1.0f;
		fConst122 = 1.0f / fConst6;
		fConst123 = (fConst5 + -1.4142135f) / fConst4 + 1.0f;
		fConst124 = 2.0f * (1.0f - 1.0f / mydsp_faustpower2_f(fConst4));
	}
	
	virtual void instanceResetUserInterface() {
		fCheckbox0 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox1 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox2 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider0 = static_cast<FAUSTFLOAT>(-85.0f);
		fHslider1 = static_cast<FAUSTFLOAT>(0.85f);
		fHslider2 = static_cast<FAUSTFLOAT>(0.5f);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			fVec0[l0] = 0.0f;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fRec25[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			fRec27[l2] = 0.0f;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			iVec1[l3] = 0;
		}
		for (int l4 = 0; l4 < 2; l4 = l4 + 1) {
			iRec28[l4] = 0;
		}
		for (int l5 = 0; l5 < 2; l5 = l5 + 1) {
			fRec26[l5] = 0.0f;
		}
		for (int l6 = 0; l6 < 2; l6 = l6 + 1) {
			fVec2[l6] = 0.0f;
		}
		for (int l7 = 0; l7 < 2; l7 = l7 + 1) {
			fRec24[l7] = 0.0f;
		}
		for (int l8 = 0; l8 < 3; l8 = l8 + 1) {
			fRec23[l8] = 0.0f;
		}
		for (int l9 = 0; l9 < 3; l9 = l9 + 1) {
			fRec22[l9] = 0.0f;
		}
		for (int l10 = 0; l10 < 2; l10 = l10 + 1) {
			fVec3[l10] = 0.0f;
		}
		for (int l11 = 0; l11 < 2; l11 = l11 + 1) {
			fRec21[l11] = 0.0f;
		}
		for (int l12 = 0; l12 < 2; l12 = l12 + 1) {
			fRec20[l12] = 0.0f;
		}
		for (int l13 = 0; l13 < 2; l13 = l13 + 1) {
			fRec29[l13] = 0.0f;
		}
		for (int l14 = 0; l14 < 2; l14 = l14 + 1) {
			fVec4[l14] = 0.0f;
		}
		for (int l15 = 0; l15 < 2; l15 = l15 + 1) {
			fRec19[l15] = 0.0f;
		}
		for (int l16 = 0; l16 < 2; l16 = l16 + 1) {
			fRec18[l16] = 0.0f;
		}
		for (int l17 = 0; l17 < 2; l17 = l17 + 1) {
			fRec17[l17] = 0.0f;
		}
		for (int l18 = 0; l18 < 2; l18 = l18 + 1) {
			fVec5[l18] = 0.0f;
		}
		for (int l19 = 0; l19 < 2; l19 = l19 + 1) {
			fRec16[l19] = 0.0f;
		}
		for (int l20 = 0; l20 < 2; l20 = l20 + 1) {
			fRec15[l20] = 0.0f;
		}
		for (int l21 = 0; l21 < 2; l21 = l21 + 1) {
			fRec14[l21] = 0.0f;
		}
		for (int l22 = 0; l22 < 2; l22 = l22 + 1) {
			fVec6[l22] = 0.0f;
		}
		for (int l23 = 0; l23 < 2; l23 = l23 + 1) {
			fRec13[l23] = 0.0f;
		}
		for (int l24 = 0; l24 < 4; l24 = l24 + 1) {
			fRec12[l24] = 0.0f;
		}
		for (int l25 = 0; l25 < 3; l25 = l25 + 1) {
			fRec11[l25] = 0.0f;
		}
		for (int l26 = 0; l26 < 3; l26 = l26 + 1) {
			fRec30[l26] = 0.0f;
		}
		for (int l27 = 0; l27 < 3; l27 = l27 + 1) {
			fRec10[l27] = 0.0f;
		}
		for (int l28 = 0; l28 < 2; l28 = l28 + 1) {
			fVec7[l28] = 0.0f;
		}
		for (int l29 = 0; l29 < 2; l29 = l29 + 1) {
			fRec9[l29] = 0.0f;
		}
		for (int l30 = 0; l30 < 2; l30 = l30 + 1) {
			fRec31[l30] = 0.0f;
		}
		for (int l31 = 0; l31 < 2; l31 = l31 + 1) {
			fRec32[l31] = 0.0f;
		}
		for (int l32 = 0; l32 < 2; l32 = l32 + 1) {
			fVec8[l32] = 0.0f;
		}
		for (int l33 = 0; l33 < 2; l33 = l33 + 1) {
			fRec8[l33] = 0.0f;
		}
		for (int l34 = 0; l34 < 3; l34 = l34 + 1) {
			fRec7[l34] = 0.0f;
		}
		for (int l35 = 0; l35 < 3; l35 = l35 + 1) {
			fRec6[l35] = 0.0f;
		}
		for (int l36 = 0; l36 < 3; l36 = l36 + 1) {
			fRec5[l36] = 0.0f;
		}
		for (int l37 = 0; l37 < 3; l37 = l37 + 1) {
			fRec4[l37] = 0.0f;
		}
		IOTA0 = 0;
		for (int l38 = 0; l38 < 256; l38 = l38 + 1) {
			fVec9[l38] = 0.0f;
		}
		for (int l39 = 0; l39 < 3; l39 = l39 + 1) {
			fRec3[l39] = 0.0f;
		}
		for (int l40 = 0; l40 < 3; l40 = l40 + 1) {
			fRec2[l40] = 0.0f;
		}
		for (int l41 = 0; l41 < 3; l41 = l41 + 1) {
			fRec1[l41] = 0.0f;
		}
		for (int l42 = 0; l42 < 2; l42 = l42 + 1) {
			fVec10[l42] = 0.0f;
		}
		for (int l43 = 0; l43 < 2; l43 = l43 + 1) {
			fRec0[l43] = 0.0f;
		}
	}
	
	virtual void init(int sample_rate) {
		classInit(sample_rate);
		instanceInit(sample_rate);
	}
	
	virtual void instanceInit(int sample_rate) {
		instanceConstants(sample_rate);
		instanceResetUserInterface();
		instanceClear();
	}
	
	virtual mydsp* clone() {
		return new mydsp(*this);
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("Dunwich");
		ui_interface->addCheckButton("bypass", &fCheckbox0);
		ui_interface->addCheckButton("cabBtn", &fCheckbox1);
		ui_interface->addHorizontalSlider("gain", &fHslider1, FAUSTFLOAT(0.85f), FAUSTFLOAT(0.0f), FAUSTFLOAT(2.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider0, "unit", "dB");
		ui_interface->addHorizontalSlider("gate", &fHslider0, FAUSTFLOAT(-85.0f), FAUSTFLOAT(-1e+02f), FAUSTFLOAT(0.0f), FAUSTFLOAT(0.1f));
		ui_interface->addCheckButton("lead", &fCheckbox2);
		ui_interface->addHorizontalSlider("level", &fHslider2, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* output0 = outputs[0];
		int iSlow0 = static_cast<int>(static_cast<float>(fCheckbox0));
		int iSlow1 = static_cast<int>(static_cast<float>(fCheckbox1));
		int iSlow2 = static_cast<int>(static_cast<float>(fCheckbox2));
		float fSlow3 = std::tan(fConst75 * ((iSlow2) ? 5e+02f : 7.5e+02f));
		float fSlow4 = 1.0f / fSlow3;
		float fSlow5 = 1.0f - fSlow4;
		float fSlow6 = std::pow(1e+01f, 0.05f * static_cast<float>(fHslider0));
		float fSlow7 = fSlow4 + 1.0f;
		float fSlow8 = static_cast<float>(((iSlow2) ? 5 : 10));
		float fSlow9 = fConst85 * static_cast<float>(fHslider1);
		float fSlow10 = ((iSlow2) ? 0.5f : 0.8f);
		float fSlow11 = std::exp(3.4f * (((iSlow2) ? 0.44f : 0.3f) + -1.0f));
		float fSlow12 = 4.851e-08f * fSlow10;
		float fSlow13 = fConst88 * (fSlow10 * (4.851e-06f * fSlow11 + -4.2449e-07f - fSlow12) + 4.972e-05f * fSlow11 + 7.172e-07f);
		float fSlow14 = 0.00022f * fSlow10;
		float fSlow15 = 0.02205f * fSlow11;
		float fSlow16 = fConst87 * (fSlow14 + fSlow15 + 0.0046705f);
		float fSlow17 = 2.662e-10f * fSlow11 - 2.662e-12f * fSlow10;
		float fSlow18 = 2.42e-09f * fSlow11;
		float fSlow19 = fConst89 * (fSlow10 * (fSlow17 + -2.1538e-11f) + fSlow18 + 2.42e-11f);
		float fSlow20 = fSlow13 - (fSlow16 + 3.0f * (1.0f - fSlow19));
		float fSlow21 = fSlow16 + fSlow13;
		float fSlow22 = fSlow21 - 3.0f * (fSlow19 + 1.0f);
		float fSlow23 = fSlow16 + fSlow19 + (-1.0f - fSlow13);
		float fSlow24 = -1.0f - (fSlow21 + fSlow19);
		float fSlow25 = ((iSlow2) ? 0.8f : 0.35f);
		float fSlow26 = fConst88 * (2.2e-07f * fSlow25 + fSlow10 * (5.951e-08f - fSlow12) + fSlow11 * (4.851e-06f * fSlow10 + 1.32e-06f) + 1.32e-08f);
		float fSlow27 = fSlow10 * (fSlow17 + 2.662e-12f) + fSlow25 * (fSlow18 + 2.42e-11f * (1.0f - fSlow10));
		float fSlow28 = fConst90 * fSlow27;
		float fSlow29 = fConst87 * (fSlow15 + fSlow14 + 5e-05f * fSlow25 + 0.0002205f);
		float fSlow30 = fSlow26 + fSlow28 - fSlow29;
		float fSlow31 = fSlow29 + fSlow26;
		float fSlow32 = fSlow31 - fSlow28;
		float fSlow33 = fConst89 * fSlow27;
		float fSlow34 = fSlow29 + fSlow33 - fSlow26;
		float fSlow35 = fSlow31 + fSlow33;
		float fSlow36 = fConst85 * static_cast<float>(fHslider2);
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			float fTemp0 = static_cast<float>(input0[i0]);
			float fTemp1 = ((iSlow0) ? 0.0f : fTemp0);
			fVec0[0] = fTemp1;
			fRec25[0] = fConst2 * (fTemp1 - fVec0[1] + fConst3 * fRec25[1]);
			fRec27[0] = fConst77 * std::fabs(fRec25[0]) + fConst76 * fRec27[1];
			int iTemp2 = fRec27[0] > fSlow6;
			iVec1[0] = iTemp2;
			iRec28[0] = std::max<int>(iConst78 * (iTemp2 < iVec1[1]), iRec28[1] + -1);
			float fTemp3 = std::fabs(std::max<float>(static_cast<float>(iTemp2), static_cast<float>(iRec28[0] > 0)));
			float fTemp4 = ((fTemp3 > fRec26[1]) ? fConst76 : fConst79);
			fRec26[0] = fTemp3 * (1.0f - fTemp4) + fRec26[1] * fTemp4;
			float fTemp5 = fRec25[0] * fRec26[0];
			fVec2[0] = fTemp5;
			fRec24[0] = -((fRec24[1] * fSlow5 - (fTemp5 - fVec2[1]) / fSlow3) / fSlow7);
			fRec23[0] = tanhf(7.0f * fRec24[0]) - fConst80 * (fConst81 * fRec23[2] + fConst82 * fRec23[1]);
			fRec22[0] = 0.16666667f * tanhf(fConst74 * (fRec23[2] + fRec23[0] + 2.0f * fRec23[1])) - fConst70 * (fConst83 * fRec22[2] + fConst84 * fRec22[1]);
			float fTemp6 = ((iSlow2) ? fRec24[0] : fConst70 * (fRec22[2] + fRec22[0] + 2.0f * fRec22[1]));
			fVec3[0] = fTemp6;
			fRec21[0] = -(fConst66 * (fConst67 * fRec21[1] - fConst65 * (fTemp6 - fVec3[1])));
			fRec20[0] = -(fConst63 * (fConst64 * fRec20[1] - (fRec21[0] + fRec21[1])));
			fRec29[0] = fSlow9 + fConst86 * fRec29[1];
			float fTemp7 = 0.8f * fRec29[0] + 0.2f;
			float fTemp8 = tanhf(fRec20[0] * fSlow8 * fTemp7 + -0.5f);
			fVec4[0] = fTemp8;
			fRec19[0] = fConst2 * (fTemp8 - fVec4[1] + fConst3 * fRec19[1]);
			fRec18[0] = -(fConst60 * (fConst61 * fRec18[1] - fConst59 * (fRec19[0] - fRec19[1])));
			fRec17[0] = -(fConst57 * (fConst58 * fRec17[1] - (fRec18[0] + fRec18[1])));
			float fTemp9 = tanhf(fRec17[0] * fSlow8 * fTemp7 + 0.71f);
			fVec5[0] = fTemp9;
			fRec16[0] = fConst2 * (fTemp9 - fVec5[1] + fConst3 * fRec16[1]);
			fRec15[0] = -(fConst54 * (fConst55 * fRec15[1] - fConst53 * (fRec16[0] - fRec16[1])));
			fRec14[0] = -(fConst51 * (fConst52 * fRec14[1] - (fRec15[0] + fRec15[1])));
			float fTemp10 = tanhf(fRec14[0] * fSlow8 * fTemp7 + 0.18f);
			fVec6[0] = fTemp10;
			fRec13[0] = fConst2 * (fTemp10 - fVec6[1] + fConst3 * fRec13[1]);
			fRec12[0] = ((iSlow2) ? 1.5f * fRec13[0] : fRec13[0]) - (fRec12[1] * fSlow20 + fRec12[2] * fSlow22 + fRec12[3] * fSlow23) / fSlow24;
			float fTemp11 = (fRec12[1] * fSlow30 + fRec12[2] * fSlow32 + fRec12[3] * fSlow34 - fRec12[0] * fSlow35) / fSlow24;
			fRec11[0] = fTemp11 - fConst49 * (fConst91 * fRec11[2] + fConst92 * fRec11[1]);
			fRec30[0] = fTemp11 - fConst95 * (fConst96 * fRec30[2] + fConst97 * fRec30[1]);
			float fTemp12 = fConst46 * fRec10[1];
			fRec10[0] = ((iSlow2) ? fConst95 * (fRec30[2] + fRec30[0] + 2.0f * fRec30[1]) : fConst49 * (fRec11[2] + fRec11[0] + 2.0f * fRec11[1])) - fConst45 * (fConst98 * fRec10[2] + fTemp12);
			float fTemp13 = fTemp12 + fConst100 * fRec10[0] + fConst101 * fRec10[2];
			fVec7[0] = fTemp13;
			fRec9[0] = -(fConst38 * (fConst39 * fRec9[1] - fConst45 * (fTemp13 + fVec7[1])));
			fRec31[0] = -(fConst38 * (fConst39 * fRec31[1] - fConst102 * (fTemp13 - fVec7[1])));
			fRec32[0] = fSlow36 + fConst86 * fRec32[1];
			float fTemp14 = 16.0f * ((iSlow2) ? fConst45 * fTemp13 : fRec9[0] + 1.4125376f * fRec31[0]) * std::pow(1e+01f, 0.05f * (24.0f * (fRec32[0] + -0.5f) + -3e+01f));
			float fTemp15 = ((iSlow1) ? 0.0f : fTemp14);
			fVec8[0] = fTemp15;
			fRec8[0] = fConst2 * (fTemp15 - fVec8[1] + fConst3 * fRec8[1]);
			fRec7[0] = fRec8[0] - fConst103 * (fConst104 * fRec7[2] + fConst105 * fRec7[1]);
			float fTemp16 = fConst30 * fRec6[1];
			fRec6[0] = fConst35 * (fRec7[2] + (fRec7[0] - 2.0f * fRec7[1])) - fConst29 * (fConst106 * fRec6[2] + fTemp16);
			float fTemp17 = fConst24 * fRec5[1];
			fRec5[0] = fConst29 * (fTemp16 + fConst108 * fRec6[0] + fConst109 * fRec6[2]) - fConst23 * (fConst110 * fRec5[2] + fTemp17);
			float fTemp18 = fConst18 * fRec4[1];
			fRec4[0] = fConst23 * (fTemp17 + fConst112 * fRec5[0] + fConst113 * fRec5[2]) - fConst17 * (fConst114 * fRec4[2] + fTemp18);
			float fTemp19 = fTemp18 + fConst116 * fRec4[0] + fConst117 * fRec4[2];
			fVec9[IOTA0 & 255] = fTemp19;
			fRec3[0] = fConst17 * (fTemp19 + 0.12f * fVec9[(IOTA0 - iConst118) & 255]) - fConst11 * (fConst119 * fRec3[2] + fConst120 * fRec3[1]);
			fRec2[0] = fConst11 * (fRec3[2] + fRec3[0] + 2.0f * fRec3[1]) - fConst10 * (fConst121 * fRec2[2] + fConst120 * fRec2[1]);
			fRec1[0] = fConst10 * (fRec2[2] + fRec2[0] + 2.0f * fRec2[1]) - fConst122 * (fConst123 * fRec1[2] + fConst124 * fRec1[1]);
			float fTemp20 = tanhf(fConst7 * (fRec1[2] + fRec1[0] + 2.0f * fRec1[1]));
			fVec10[0] = fTemp20;
			fRec0[0] = fConst2 * (fConst3 * fRec0[1] + 0.95f * (fTemp20 - fVec10[1]));
			output0[i0] = static_cast<FAUSTFLOAT>(((iSlow0) ? fTemp0 : ((iSlow1) ? fTemp14 : fRec0[0])));
			fVec0[1] = fVec0[0];
			fRec25[1] = fRec25[0];
			fRec27[1] = fRec27[0];
			iVec1[1] = iVec1[0];
			iRec28[1] = iRec28[0];
			fRec26[1] = fRec26[0];
			fVec2[1] = fVec2[0];
			fRec24[1] = fRec24[0];
			fRec23[2] = fRec23[1];
			fRec23[1] = fRec23[0];
			fRec22[2] = fRec22[1];
			fRec22[1] = fRec22[0];
			fVec3[1] = fVec3[0];
			fRec21[1] = fRec21[0];
			fRec20[1] = fRec20[0];
			fRec29[1] = fRec29[0];
			fVec4[1] = fVec4[0];
			fRec19[1] = fRec19[0];
			fRec18[1] = fRec18[0];
			fRec17[1] = fRec17[0];
			fVec5[1] = fVec5[0];
			fRec16[1] = fRec16[0];
			fRec15[1] = fRec15[0];
			fRec14[1] = fRec14[0];
			fVec6[1] = fVec6[0];
			fRec13[1] = fRec13[0];
			for (int j0 = 3; j0 > 0; j0 = j0 - 1) {
				fRec12[j0] = fRec12[j0 - 1];
			}
			fRec11[2] = fRec11[1];
			fRec11[1] = fRec11[0];
			fRec30[2] = fRec30[1];
			fRec30[1] = fRec30[0];
			fRec10[2] = fRec10[1];
			fRec10[1] = fRec10[0];
			fVec7[1] = fVec7[0];
			fRec9[1] = fRec9[0];
			fRec31[1] = fRec31[0];
			fRec32[1] = fRec32[0];
			fVec8[1] = fVec8[0];
			fRec8[1] = fRec8[0];
			fRec7[2] = fRec7[1];
			fRec7[1] = fRec7[0];
			fRec6[2] = fRec6[1];
			fRec6[1] = fRec6[0];
			fRec5[2] = fRec5[1];
			fRec5[1] = fRec5[0];
			fRec4[2] = fRec4[1];
			fRec4[1] = fRec4[0];
			IOTA0 = IOTA0 + 1;
			fRec3[2] = fRec3[1];
			fRec3[1] = fRec3[0];
			fRec2[2] = fRec2[1];
			fRec2[1] = fRec2[0];
			fRec1[2] = fRec1[1];
			fRec1[1] = fRec1[0];
			fVec10[1] = fVec10[0];
			fRec0[1] = fRec0[0];
		}
	}

};

// END-FAUSTDSP

#endif
