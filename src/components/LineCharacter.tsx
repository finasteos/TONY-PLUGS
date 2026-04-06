import { motion } from "motion/react";

export const LineCharacter = () => {
  return (
    <div className="relative h-64 w-full flex items-end justify-center overflow-hidden bg-blue-600">
      {/* The Line */}
      <motion.div 
        className="absolute bottom-12 left-0 right-0 h-1 bg-white"
        initial={{ scaleX: 0 }}
        animate={{ scaleX: 1 }}
        transition={{ duration: 1.5, ease: "easeInOut" }}
      />
      
      {/* The Character (Simple SVG representation) */}
      <motion.div
        className="relative z-10 mb-12"
        initial={{ x: -200, opacity: 0 }}
        animate={{ x: 0, opacity: 1 }}
        transition={{ delay: 1, duration: 1, type: "spring" }}
      >
        <svg width="100" height="150" viewBox="0 0 100 150" fill="none" xmlns="http://www.w3.org/2000/svg">
          <defs>
            <filter id="inkBleedCharacter">
              <feGaussianBlur in="SourceGraphic" stdDeviation="0.8" result="blur" />
              <feColorMatrix in="blur" mode="matrix" values="1 0 0 0 0  0 1 0 0 0  0 0 1 0 0  0 0 0 18 -7" result="ink" />
              <feComposite in="SourceGraphic" in2="ink" operator="atop" />
            </filter>
          </defs>
          {/* Head & Body Outline */}
          <motion.path
            d="M50 30 C 70 30, 80 50, 80 70 C 80 90, 70 110, 50 110 C 30 110, 20 90, 20 70 C 20 50, 30 30, 50 30"
            stroke="white"
            strokeWidth="4"
            strokeLinecap="round"
            filter="url(#inkBleedCharacter)"
            initial={{ pathLength: 0 }}
            animate={{ 
              pathLength: 1,
              strokeWidth: [4, 5, 3.5, 4]
            }}
            transition={{ 
              pathLength: { duration: 2, repeat: Infinity, repeatType: "reverse" },
              strokeWidth: { duration: 3, repeat: Infinity, ease: "easeInOut" }
            }}
          />
          {/* Nose (Iconic part of La Linea) */}
          <motion.path
            d="M80 70 L 110 75 L 80 80"
            stroke="white"
            strokeWidth="4"
            strokeLinecap="round"
            filter="url(#inkBleedCharacter)"
            initial={{ pathLength: 0 }}
            animate={{ 
              pathLength: 1,
              strokeWidth: [4, 6, 4]
            }}
            transition={{ 
              pathLength: { delay: 0.5, duration: 1 },
              strokeWidth: { duration: 2, repeat: Infinity, ease: "easeInOut" }
            }}
          />
          {/* Legs */}
          <motion.path
            d="M40 110 L 35 140 M 60 110 L 65 140"
            stroke="white"
            strokeWidth="4"
            strokeLinecap="round"
            filter="url(#inkBleedCharacter)"
          />
        </svg>
      </motion.div>
      
      {/* Speech Bubble (Expressive) */}
      <motion.div
        className="absolute top-10 right-1/4 bg-white text-blue-600 px-4 py-2 rounded-full font-bold text-xl"
        initial={{ scale: 0, opacity: 0 }}
        animate={{ scale: 1, opacity: 1 }}
        transition={{ delay: 2.5, type: "spring" }}
      >
        MUMBLE!
      </motion.div>
    </div>
  );
};
