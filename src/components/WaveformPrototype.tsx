import { motion } from "motion/react";
import { useState, useEffect, useRef } from "react";

interface WaveformProps {
  color?: string;
  lineThickness?: number;
  isWobbly?: boolean;
}

export const LinusWaveform = ({ 
  color = "#1E5AA8", 
  lineThickness = 6,
  isWobbly = true 
}: WaveformProps) => {
  const [phase, setPhase] = useState(0);
  const containerRef = useRef<HTMLDivElement>(null);
  const [points, setPoints] = useState<number[]>([]);

  // Generate a static-ish waveform buffer
  useEffect(() => {
    const newPoints = Array.from({ length: 100 }, (_, i) => {
      return Math.sin(i * 0.2) * 0.5 + Math.sin(i * 0.5) * 0.2;
    });
    setPoints(newPoints);
  }, []);

  // Animation loop for the "wobble"
  useEffect(() => {
    let animationFrame: number;
    const animate = () => {
      setPhase(prev => prev + 0.05);
      animationFrame = requestAnimationFrame(animate);
    };
    if (isWobbly) animationFrame = requestAnimationFrame(animate);
    return () => cancelAnimationFrame(animationFrame);
  }, [isWobbly]);

  const generatePath = () => {
    if (points.length === 0) return "";
    
    const width = 800;
    const height = 200;
    const step = width / (points.length - 1);
    
    let d = "";
    points.forEach((p, i) => {
      const x = i * step;
      // Add the "Linus Wobble" - subtle imperfection
      const wobble = isWobbly ? Math.sin(i * 0.1 + phase) * 3 : 0;
      const y = (height / 2) + (p * height * 0.4) + wobble;
      
      if (i === 0) d += `M ${x} ${y}`;
      else d += ` L ${x} ${y}`;
    });
    
    return d;
  };

  return (
    <div 
      ref={containerRef}
      className="w-full h-48 rounded-3xl border-4 border-black overflow-hidden relative shadow-[8px_8px_0px_0px_rgba(0,0,0,1)]"
      style={{ backgroundColor: color }}
    >
      <svg 
        viewBox="0 0 800 200" 
        className="w-full h-full preserve-3d"
        preserveAspectRatio="none"
      >
        <defs>
          <filter id="inkBleed">
            <feGaussianBlur in="SourceGraphic" stdDeviation="1" result="blur" />
            <feColorMatrix in="blur" mode="matrix" values="1 0 0 0 0  0 1 0 0 0  0 0 1 0 0  0 0 0 18 -7" result="ink" />
            <feComposite in="SourceGraphic" in2="ink" operator="atop" />
          </filter>
        </defs>
        <motion.path
          d={generatePath()}
          stroke="white"
          strokeWidth={lineThickness}
          fill="none"
          strokeLinecap="round"
          strokeLinejoin="round"
          filter="url(#inkBleed)"
          animate={{ 
            strokeWidth: [lineThickness, lineThickness * 1.2, lineThickness * 0.9, lineThickness] 
          }}
          transition={{ 
            duration: 3, 
            repeat: Infinity, 
            ease: "easeInOut" 
          }}
        />
      </svg>
      <div className="absolute top-4 left-6 text-[10px] font-black text-white uppercase tracking-widest opacity-50">
        Variable Width Waveform
      </div>
    </div>
  );
};
