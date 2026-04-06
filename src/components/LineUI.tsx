import { motion } from "motion/react";
import { ArrowRight, Check, X, Info, AlertCircle } from "lucide-react";

export const LineUI = () => {
  return (
    <div className="space-y-16 p-8">
      {/* Section: Buttons */}
      <section className="space-y-8">
        <h3 className="text-2xl font-black uppercase tracking-tighter border-b-4 border-black inline-block mb-8">Buttons & Interaction</h3>
        <div className="flex flex-wrap gap-6">
          <motion.button 
            whileHover={{ scale: 1.05, x: 5 }}
            whileTap={{ scale: 0.95 }}
            className="bg-black text-white px-8 py-4 rounded-full font-black uppercase flex items-center gap-3 border-4 border-black hover:bg-white hover:text-black transition-colors"
          >
            <span>Primary Action</span>
            <ArrowRight className="w-5 h-5" />
          </motion.button>

          <motion.button 
            whileHover={{ scale: 1.05, y: -5 }}
            whileTap={{ scale: 0.95 }}
            className="bg-white text-black px-8 py-4 rounded-full font-black uppercase flex items-center gap-3 border-4 border-black hover:bg-black hover:text-white transition-colors"
          >
            <span>Secondary</span>
          </motion.button>

          <motion.button 
            whileHover={{ rotate: 5 }}
            whileTap={{ rotate: -5 }}
            className="bg-yellow-400 text-black px-8 py-4 rounded-full font-black uppercase flex items-center gap-3 border-4 border-black shadow-[8px_8px_0px_0px_rgba(0,0,0,1)]"
          >
            <span>Brutalist</span>
          </motion.button>
        </div>
      </section>

      {/* Section: Cards */}
      <section className="space-y-8">
        <h3 className="text-2xl font-black uppercase tracking-tighter border-b-4 border-black inline-block mb-8">Cards & Information</h3>
        <div className="grid grid-cols-1 md:grid-cols-3 gap-8">
          {/* Info Card */}
          <div className="bg-blue-500 p-6 rounded-3xl border-4 border-black text-white relative overflow-hidden group">
            <div className="absolute top-0 right-0 p-4 opacity-20 group-hover:opacity-100 transition-opacity">
              <Info className="w-12 h-12" />
            </div>
            <h4 className="text-xl font-black uppercase mb-4">System Info</h4>
            <p className="text-sm font-medium leading-relaxed mb-6">
              The line is continuous. It never breaks. It is the beginning and the end of all design.
            </p>
            <div className="h-1 bg-white w-full rounded-full" />
          </div>

          {/* Alert Card */}
          <div className="bg-red-500 p-6 rounded-3xl border-4 border-black text-white relative overflow-hidden group">
            <div className="absolute top-0 right-0 p-4 opacity-20 group-hover:opacity-100 transition-opacity">
              <AlertCircle className="w-12 h-12" />
            </div>
            <h4 className="text-xl font-black uppercase mb-4">Warning</h4>
            <p className="text-sm font-medium leading-relaxed mb-6">
              Do not cross the line. The character might get angry and start mumbling.
            </p>
            <div className="h-1 bg-white w-1/2 rounded-full" />
          </div>

          {/* Success Card */}
          <div className="bg-green-500 p-6 rounded-3xl border-4 border-black text-white relative overflow-hidden group">
            <div className="absolute top-0 right-0 p-4 opacity-20 group-hover:opacity-100 transition-opacity">
              <Check className="w-12 h-12" />
            </div>
            <h4 className="text-xl font-black uppercase mb-4">Success</h4>
            <p className="text-sm font-medium leading-relaxed mb-6">
              The line has been drawn correctly. The animation is now fluid and expressive.
            </p>
            <div className="h-1 bg-white w-full rounded-full" />
          </div>
        </div>
      </section>

      {/* Section: Input Fields */}
      <section className="space-y-8">
        <h3 className="text-2xl font-black uppercase tracking-tighter border-b-4 border-black inline-block mb-8">Inputs & Forms</h3>
        <div className="max-w-md space-y-6">
          <div className="space-y-2">
            <label className="text-xs font-black uppercase tracking-widest ml-4">Username</label>
            <input 
              type="text" 
              placeholder="Type something..."
              className="w-full px-6 py-4 rounded-full border-4 border-black focus:outline-none focus:ring-4 focus:ring-blue-400 transition-all font-bold placeholder:text-gray-400"
            />
          </div>
          <div className="flex gap-4">
            <div className="flex-1 space-y-2">
              <label className="text-xs font-black uppercase tracking-widest ml-4">Option A</label>
              <div className="w-full h-14 rounded-full border-4 border-black bg-white flex items-center justify-center cursor-pointer hover:bg-gray-100 transition-colors">
                <Check className="w-6 h-6 text-green-600" />
              </div>
            </div>
            <div className="flex-1 space-y-2">
              <label className="text-xs font-black uppercase tracking-widest ml-4">Option B</label>
              <div className="w-full h-14 rounded-full border-4 border-black bg-white flex items-center justify-center cursor-pointer hover:bg-gray-100 transition-colors">
                <X className="w-6 h-6 text-red-600" />
              </div>
            </div>
          </div>
        </div>
      </section>
    </div>
  );
};
