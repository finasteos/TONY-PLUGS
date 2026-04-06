import { Terminal, Code2, Layers, Cpu } from "lucide-react";

export const JuceReference = () => {
  const snippets = [
    {
      title: "Ink Bleed (Option A)",
      desc: "Multi-pass rendering for soft edges.",
      code: `void drawInkBleedPath(juce::Graphics& g, const juce::Path& path, float baseThickness, juce::Colour color) {
  // Layer 1: Wide, soft blur
  g.setColour(color.withAlpha(0.3f));
  g.strokePath(path, juce::PathStrokeType(baseThickness * 1.4f, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
  
  // Layer 2: Core line
  g.setColour(color);
  g.strokePath(path, juce::PathStrokeType(baseThickness, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
}`,
      icon: <Layers className="w-5 h-5" />
    },
    {
      title: "Linus Wobble Path",
      desc: "1:1 port of our TypeScript logic.",
      code: `juce::Path generateWobblyPath(const std::vector<float>& points, float width, float height, float phase, bool isWobbly) {
  juce::Path path;
  float step = width / (float)(points.size() - 1);
  for (size_t i = 0; i < points.size(); ++i) {
    float x = i * step;
    float y = (height / 2.0f) + (points[i] * height * 0.4f);
    if (isWobbly) {
      float wobble = std::sin(i * 0.1f + phase) * 3.0f + std::sin(i * 0.03f + phase * 0.5f) * 1.5f;
      y += wobble;
    }
    if (i == 0) path.startNewSubPath(x, y);
    else path.lineTo(x, y);
  }
  return path;
}`,
      icon: <Code2 className="w-5 h-5" />
    },
    {
      title: "Chunky Knob (12px)",
      desc: "Custom drawRotarySlider implementation.",
      code: `void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos, float startAngle, float endAngle, juce::Slider& slider) {
  auto centre = getLocalBounds().toFloat().getCentre();
  float radius = width / 2.0f - 15.0f;
  // Background track
  g.setColour(juce::Colours::white.withAlpha(0.2f));
  g.drawEllipse(centre.x - radius, centre.y - radius, radius * 2, radius * 2, 12.0f);
  // Active arc
  g.setColour(juce::Colours::white);
  juce::Path arc;
  arc.addCentredArc(centre.x, centre.y, radius, radius, 0.0f, startAngle, startAngle + (endAngle - startAngle) * sliderPos, true);
  g.strokePath(arc, juce::PathStrokeType(12.0f, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
}`,
      icon: <Cpu className="w-5 h-5" />
    }
  ];

  return (
    <div className="space-y-12">
      <div className="grid grid-cols-1 lg:grid-cols-3 gap-8">
        {snippets.map((s, i) => (
          <div key={i} className="bg-black rounded-3xl border-4 border-black overflow-hidden shadow-[8px_8px_0px_0px_rgba(0,0,0,1)]">
            <div className="bg-white p-6 border-b-4 border-black flex items-center gap-4">
              <div className="bg-black text-white p-2 rounded-xl">
                {s.icon}
              </div>
              <div>
                <h3 className="font-black uppercase text-sm tracking-tighter">{s.title}</h3>
                <p className="text-[10px] font-bold opacity-60 uppercase">{s.desc}</p>
              </div>
            </div>
            <div className="p-6 bg-[#1a1a1a]">
              <pre className="text-[10px] text-green-400 font-mono overflow-x-auto whitespace-pre-wrap leading-relaxed">
                {s.code}
              </pre>
            </div>
          </div>
        ))}
      </div>
      
      <div className="bg-yellow-400 p-8 rounded-[40px] border-4 border-black shadow-[12px_12px_0px_0px_rgba(0,0,0,1)] flex flex-col md:flex-row items-center gap-8">
        <div className="bg-black text-white p-6 rounded-full">
          <Terminal className="w-12 h-12" />
        </div>
        <div>
          <h3 className="text-2xl font-black uppercase tracking-tighter mb-2">Kimi's Porting Strategy</h3>
          <p className="font-bold text-sm leading-relaxed max-w-2xl">
            "Start with the knob and wobble — you'll have something that feels like Linus immediately. 
            Add the ink bleed later if the flat look isn't 'analog' enough. Option A (Multi-pass) 
            is 90% of the look with 10% of the complexity."
          </p>
        </div>
      </div>
    </div>
  );
};
