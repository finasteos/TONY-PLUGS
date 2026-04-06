import { motion } from "motion/react";
import { LineCharacter } from "./components/LineCharacter";
import { VSTPlugin } from "./components/VSTPlugin";
import { LineUI } from "./components/LineUI";
import { LinusWaveform } from "./components/WaveformPrototype";
import { Info, Palette, Music, Layout, ArrowDown, Cpu, Terminal, Code } from "lucide-react";

export default function App() {
  return (
    <div className="min-h-screen bg-[#f0f0f0] text-black font-sans selection:bg-blue-500 selection:text-white overflow-x-hidden">
      {/* Hero Section */}
      <header className="relative h-screen flex flex-col items-center justify-center bg-blue-600 text-white overflow-hidden">
        <div className="absolute inset-0 opacity-10 pointer-events-none">
          <svg className="w-full h-full" viewBox="0 0 100 100" preserveAspectRatio="none">
            <path d="M0 50 Q 25 40, 50 50 T 100 50" stroke="white" strokeWidth="0.5" fill="none" />
            <path d="M0 60 Q 25 50, 50 60 T 100 60" stroke="white" strokeWidth="0.5" fill="none" />
            <path d="M0 40 Q 25 30, 50 40 T 100 40" stroke="white" strokeWidth="0.5" fill="none" />
          </svg>
        </div>

        <motion.div 
          initial={{ y: 50, opacity: 0 }}
          animate={{ y: 0, opacity: 1 }}
          transition={{ duration: 0.8, ease: "easeOut" }}
          className="z-10 text-center px-4"
        >
          <h1 className="text-7xl md:text-9xl font-black uppercase tracking-tighter mb-4">
            LA LINEA
          </h1>
          <p className="text-xl md:text-2xl font-medium max-w-2xl mx-auto opacity-90 leading-relaxed mb-12">
            A minimalist design system inspired by the iconic animation of Osvaldo Cavandoli & the Amiga Demoscene.
          </p>
          <motion.div
            animate={{ y: [0, 10, 0] }}
            transition={{ repeat: Infinity, duration: 2 }}
          >
            <ArrowDown className="w-10 h-10 mx-auto" />
          </motion.div>
        </motion.div>

        {/* The Animated Character Component */}
        <div className="absolute bottom-0 left-0 right-0">
          <LineCharacter />
        </div>
      </header>

      {/* Amiga Legacy Section */}
      <section className="bg-black text-white py-32 px-8 border-y-8 border-white">
        <div className="max-w-5xl mx-auto grid grid-cols-1 md:grid-cols-2 gap-24 items-center">
          <div className="space-y-12">
            <div className="flex items-center gap-6">
              <Cpu className="w-12 h-12 text-blue-500" />
              <h2 className="text-5xl font-black uppercase tracking-tighter">Amiga Legacy</h2>
            </div>
            <div className="space-y-8 text-xl font-medium leading-relaxed text-gray-400">
              <p>
                From <strong className="text-white">Worms graphics</strong> to <strong className="text-white">La Linea</strong>, the lineage of minimalist Scandinavian design is rooted in the "doing a lot with very little" mindset of the Amiga demoscene.
              </p>
              <div className="flex gap-4">
                <div className="bg-blue-600 p-4 rounded-2xl border-4 border-white">
                  <Terminal className="w-8 h-8" />
                </div>
                <div className="bg-red-600 p-4 rounded-2xl border-4 border-white">
                  <Code className="w-8 h-8" />
                </div>
              </div>
              <p className="text-sm italic">
                "Design your hardware sprites in Figma, animate them in code."
              </p>
            </div>
          </div>
          <div className="relative aspect-square bg-[#1E5AA8] rounded-[60px] border-8 border-white flex items-center justify-center overflow-hidden shadow-[32px_32px_0px_0px_rgba(255,255,255,0.1)]">
            <motion.div
              animate={{ 
                rotate: [0, 90, 180, 270, 360],
                scale: [1, 1.1, 1]
              }}
              transition={{ repeat: Infinity, duration: 10, ease: "linear" }}
              className="w-48 h-48 border-[12px] border-white rounded-full flex items-center justify-center"
            >
              <div className="w-24 h-2 bg-white rounded-full" />
            </motion.div>
            <div className="absolute top-8 left-8 text-xs font-black uppercase tracking-[0.2em]">Sprite-01</div>
          </div>
        </div>
      </section>

      {/* Smart Prototyping Section */}
      <section className="py-32 px-8 bg-white">
        <div className="max-w-5xl mx-auto space-y-16">
          <div className="text-center space-y-4">
            <h2 className="text-5xl font-black uppercase tracking-tighter">Smart Prototyping</h2>
            <p className="text-gray-500 max-w-2xl mx-auto font-medium">
              Testing the "feel" of interactions quickly in TypeScript before porting to JUCE C++.
            </p>
          </div>
          <div className="grid grid-cols-1 md:grid-cols-2 gap-12">
            <LinusWaveform color="#1E5AA8" />
            <LinusWaveform color="#2E8B57" />
          </div>
        </div>
      </section>

      {/* VST Plugin Section */}
      <section className="bg-black py-32 px-8">
        <div className="max-w-5xl mx-auto space-y-16">
          <div className="text-center space-y-4">
            <div className="flex items-center justify-center gap-4 text-white">
              <Music className="w-10 h-10" />
              <h2 className="text-5xl font-black uppercase tracking-tighter">JUCE Implementation</h2>
            </div>
            <p className="text-gray-400 max-w-xl mx-auto font-medium">
              Applying the "LinusLookAndFeel" to JUCE. Thick white tracks, rounded thumbs, and wobbly waveform displays.
            </p>
          </div>
          <VSTPlugin />
        </div>
      </section>

      {/* UI Components Section */}
      <section className="py-32 px-8 bg-white">
        <div className="max-w-5xl mx-auto space-y-16">
          <div className="flex items-center gap-4 text-black">
            <Layout className="w-10 h-10" />
            <h2 className="text-5xl font-black uppercase tracking-tighter">UI Components</h2>
          </div>
          <LineUI />
        </div>
      </section>

      {/* Animation Principles Section */}
      <section className="bg-yellow-400 py-32 px-8 border-t-8 border-black">
        <div className="max-w-5xl mx-auto grid grid-cols-1 md:grid-cols-2 gap-16">
          <div className="space-y-8">
            <div className="flex items-center gap-4 text-black">
              <Palette className="w-10 h-10" />
              <h2 className="text-4xl font-black uppercase tracking-tighter">Animation Principles</h2>
            </div>
            <ul className="space-y-6">
              {[
                "Fluidity: Motion should feel like ink flowing on paper.",
                "Exaggeration: Use squash and stretch to convey emotion.",
                "Anticipation: The line 'prepares' for a change before it happens.",
                "Staging: Keep the focus on the line's interaction with the void."
              ].map((item, i) => (
                <motion.li 
                  key={i}
                  initial={{ x: -20, opacity: 0 }}
                  whileInView={{ x: 0, opacity: 1 }}
                  transition={{ delay: i * 0.1 }}
                  className="flex items-start gap-4 text-lg font-bold"
                >
                  <div className="w-6 h-6 rounded-full border-4 border-black bg-white flex-shrink-0 mt-1" />
                  <span>{item}</span>
                </motion.li>
              ))}
            </ul>
          </div>
          <div className="relative h-64 bg-black rounded-3xl border-4 border-black flex items-center justify-center overflow-hidden">
             <motion.div
               animate={{ 
                 scale: [1, 1.2, 1],
                 rotate: [0, 180, 360],
                 borderRadius: ["20%", "50%", "20%"]
               }}
               transition={{ repeat: Infinity, duration: 4 }}
               className="w-32 h-32 border-8 border-white"
             />
             <div className="absolute bottom-4 right-4 text-[10px] text-white font-mono uppercase opacity-50">
               STYLIZED GEOMETRY
             </div>
          </div>
        </div>
      </section>

      {/* Footer */}
      <footer className="bg-black text-white py-12 px-8 border-t-4 border-white">
        <div className="max-w-5xl mx-auto flex flex-col md:flex-row justify-between items-center gap-8">
          <div className="text-2xl font-black uppercase tracking-tighter">LA LINEA</div>
          <div className="flex gap-8 text-xs font-black uppercase tracking-widest opacity-50">
            <a href="#" className="hover:opacity-100 transition-opacity">Design System</a>
            <a href="#" className="hover:opacity-100 transition-opacity">Animation</a>
            <a href="#" className="hover:opacity-100 transition-opacity">VST Plugin</a>
          </div>
          <div className="text-[10px] font-mono opacity-30">
            © 2026 INSPIRED BY CAVANDOLI & THE DEMOSCENE
          </div>
        </div>
      </footer>
    </div>
  );
}
