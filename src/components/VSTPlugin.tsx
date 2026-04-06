import { motion } from "motion/react";
import { useState, useEffect } from "react";
import { Activity, Volume2, Settings, Play, Square, Zap } from "lucide-react";

export const VSTPlugin = () => {
  const [gain, setGain] = useState(50);
  const [freq, setFreq] = useState(440);
  const [isPlaying, setIsPlaying] = useState(false);
  const [wobblePhase, setWobblePhase] = useState(0);

  // Animation loop for the "wobble"
  useEffect(() => {
    let animationFrame: number;
    const animate = () => {
      setWobblePhase(prev => prev + 0.1);
      animationFrame = requestAnimationFrame(animate);
    };
    if (isPlaying) animationFrame = requestAnimationFrame(animate);
    return () => cancelAnimationFrame(animationFrame);
  }, [isPlaying]);

  const generateWaveform = () => {
    const width = 200;
    const height = 100;
    const points = 50;
    const step = width / (points - 1);
    
    let d = "";
    for (let i = 0; i < points; i++) {
      const x = i * step;
      // Linus style: thick white line on bold background
      // Add subtle "human" wobble to the line
      const wobble = isPlaying ? Math.sin(i * 0.2 + wobblePhase) * 2 : 0;
      const y = (height / 2) + (Math.sin(i * 0.3) * (gain / 2)) + wobble;
      
      if (i === 0) d += `M ${x} ${y}`;
      else d += ` L ${x} ${y}`;
    }
    return d;
  };

  return (
    <div className="bg-[#1E5AA8] p-10 rounded-[40px] border-8 border-black shadow-[24px_24px_0px_0px_rgba(0,0,0,1)] max-w-3xl mx-auto font-mono text-white">
      {/* Header */}
      <div className="flex justify-between items-center mb-12 border-b-4 border-black pb-6">
        <div className="flex items-center gap-4">
          <div className="bg-white p-2 rounded-full border-4 border-black">
            <Zap className="w-8 h-8 text-[#1E5AA8] fill-current" />
          </div>
          <div>
            <h2 className="text-3xl font-black tracking-tighter uppercase leading-none">LINUS-SYNTH</h2>
            <span className="text-[10px] font-black opacity-70 tracking-widest uppercase">Amiga Legacy Edition v2.0</span>
          </div>
        </div>
        <div className="flex gap-4">
          <Settings className="w-8 h-8 opacity-50 hover:opacity-100 cursor-pointer transition-opacity" />
          <div className="w-4 h-4 rounded-full bg-red-500 border-2 border-black animate-pulse" />
        </div>
      </div>

      {/* Main Controls */}
      <div className="grid grid-cols-1 md:grid-cols-2 gap-16">
        {/* Left: Knobs (LinusLookAndFeel style) */}
        <div className="space-y-12">
          <div className="flex flex-col items-center">
            <label className="text-xs font-black uppercase mb-6 tracking-widest bg-black text-white px-3 py-1 rounded-full">GAIN</label>
            <div className="relative w-40 h-40 flex items-center justify-center">
              {/* Thick White Track with Rounded Ends */}
              <svg className="absolute inset-0 w-full h-full -rotate-90">
                <circle
                  cx="80"
                  cy="80"
                  r="65"
                  stroke="rgba(255,255,255,0.2)"
                  strokeWidth="12"
                  fill="none"
                  strokeLinecap="round"
                />
                <motion.circle
                  cx="80"
                  cy="80"
                  r="65"
                  stroke="white"
                  strokeWidth="12"
                  fill="none"
                  strokeLinecap="round"
                  strokeDasharray="408"
                  animate={{ strokeDashoffset: 408 - (408 * gain) / 100 }}
                  transition={{ type: "spring", stiffness: 100 }}
                />
              </svg>
              <input
                type="range"
                min="0"
                max="100"
                value={gain}
                onChange={(e) => setGain(parseInt(e.target.value))}
                className="absolute inset-0 opacity-0 cursor-pointer z-10"
              />
              <span className="text-4xl font-black drop-shadow-[2px_2px_0px_rgba(0,0,0,1)]">{gain}%</span>
            </div>
          </div>

          <div className="flex flex-col items-center">
            <label className="text-xs font-black uppercase mb-6 tracking-widest bg-black text-white px-3 py-1 rounded-full">FREQ</label>
            <div className="relative w-40 h-40 flex items-center justify-center">
              <svg className="absolute inset-0 w-full h-full -rotate-90">
                <circle
                  cx="80"
                  cy="80"
                  r="65"
                  stroke="rgba(255,255,255,0.2)"
                  strokeWidth="12"
                  fill="none"
                  strokeLinecap="round"
                />
                <motion.circle
                  cx="80"
                  cy="80"
                  r="65"
                  stroke="white"
                  strokeWidth="12"
                  fill="none"
                  strokeLinecap="round"
                  strokeDasharray="408"
                  animate={{ strokeDashoffset: 408 - (408 * (freq - 20)) / 1980 }}
                  transition={{ type: "spring", stiffness: 100 }}
                />
              </svg>
              <input
                type="range"
                min="20"
                max="2000"
                value={freq}
                onChange={(e) => setFreq(parseInt(e.target.value))}
                className="absolute inset-0 opacity-0 cursor-pointer z-10"
              />
              <span className="text-2xl font-black drop-shadow-[2px_2px_0px_rgba(0,0,0,1)]">{freq}Hz</span>
            </div>
          </div>
        </div>

        {/* Right: Visualizer & Transport */}
        <div className="flex flex-col justify-between">
          {/* Wobbly Waveform Area */}
          <div className="h-64 bg-black rounded-[32px] border-4 border-black overflow-hidden relative shadow-inner">
            <svg className="w-full h-full" viewBox="0 0 200 100" preserveAspectRatio="none">
              <defs>
                <filter id="inkBleedVST">
                  <feGaussianBlur in="SourceGraphic" stdDeviation="0.6" result="blur" />
                  <feColorMatrix in="blur" mode="matrix" values="1 0 0 0 0  0 1 0 0 0  0 0 1 0 0  0 0 0 18 -7" result="ink" />
                  <feComposite in="SourceGraphic" in2="ink" operator="atop" />
                </filter>
              </defs>
              <motion.path
                d={generateWaveform()}
                stroke="white"
                strokeWidth="6"
                fill="none"
                strokeLinecap="round"
                strokeLinejoin="round"
                filter="url(#inkBleedVST)"
                animate={{ 
                  strokeWidth: isPlaying ? [6, 8, 5, 6] : 6
                }}
                transition={{ 
                  duration: 2, 
                  repeat: Infinity, 
                  ease: "easeInOut" 
                }}
              />
            </svg>
            <div className="absolute top-4 left-6 text-[10px] font-black opacity-50 uppercase tracking-widest">WOBBLY OSCILLOSCOPE</div>
          </div>

          {/* Transport Controls (Rounded Rectangle Style) */}
          <div className="flex gap-6 mt-12">
            <motion.button 
              whileHover={{ scale: 1.05 }}
              whileTap={{ scale: 0.95 }}
              onClick={() => setIsPlaying(!isPlaying)}
              className={`flex-1 flex items-center justify-center gap-3 py-6 rounded-3xl border-4 border-black font-black uppercase transition-all shadow-[8px_8px_0px_0px_rgba(0,0,0,1)] ${
                isPlaying ? 'bg-red-600 text-white' : 'bg-white text-black hover:bg-gray-200'
              }`}
            >
              {isPlaying ? <Square className="w-6 h-6 fill-current" /> : <Play className="w-6 h-6 fill-current" />}
              <span className="text-xl tracking-tighter">{isPlaying ? 'STOP' : 'PLAY'}</span>
            </motion.button>
            <motion.button 
              whileHover={{ scale: 1.05 }}
              whileTap={{ scale: 0.95 }}
              className="p-6 rounded-3xl border-4 border-black bg-white text-black hover:bg-gray-200 shadow-[8px_8px_0px_0px_rgba(0,0,0,1)] transition-all"
            >
              <Volume2 className="w-8 h-8" />
            </motion.button>
          </div>
        </div>
      </div>

      {/* Footer Line */}
      <div className="mt-16 pt-6 border-t-4 border-black flex justify-between items-center opacity-70 text-[10px] font-black tracking-widest">
        <span>ENGINE: LINEA-CORE-AMIGA</span>
        <span>STATUS: {isPlaying ? 'GENERATING...' : 'READY'}</span>
      </div>
    </div>
  );
};
