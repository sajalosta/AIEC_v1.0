import path from "path";
import type { NextConfig } from "next";

const nextConfig: NextConfig = {
  // Parent repo has a stray package-lock.json; without this, Turbopack
  // treats that dir as [project] and RSC client manifests break.
  turbopack: {
    root: path.join(__dirname),
  },
};

export default nextConfig;
